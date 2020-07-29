#include "system_init.h"

#define DEFAULT_MPU_HZ 200            // 200Hz = 5ms
#define q30            1073741824.0f  // 2^30
#define RAD_TO_DEG     57.2957f       // 180 / pi

const signed char gyro_orientation[9] = {-1, 0, 0, 0, -1, 0, 0, 0, 1};
short gyro[3], accel[3], sensors;
unsigned long sensor_timestamp;
long quat[4];
unsigned char more;
float q0, q1, q2, q3;

void MPU6050_Interrupt_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	            
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         
	GPIO_Init(GPIOC, &GPIO_InitStructure);					     
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);
  
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							
  NVIC_Init(&NVIC_InitStructure); 
}

void MPU6050_readDMP(void) {
    dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);
    if (sensors & INV_WXYZ_QUAT ) {
        q0 = quat[0] / q30;
        q1 = quat[1] / q30;
        q2 = quat[2] / q30;
        q3 = quat[3] / q30;
        Angle_Pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * RAD_TO_DEG; 	//pitch
        Angle_Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * RAD_TO_DEG; // roll
        Angle_Yaw = atan2(2 * (q1 * q2 + q0 * q3), q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3) * RAD_TO_DEG; //yaw
        Gyro_Pitch = gyro[0] / 16.4;
        Gyro_Roll = gyro[1] / 16.4;
        Gyro_Yaw = gyro[2] / 16.4;
    }

}

int MPU6050_readTemperature(void) {
    double Temp;
    Temp = (I2C_ReadOneByte(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_TEMP_OUT_H) << 8) + I2C_ReadOneByte(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_TEMP_OUT_L);
    if (Temp > 32768) Temp -= 65536;
    Temp = (36.53 + Temp / 340.0) * 10;
    return (int)Temp;
}

void MPU6050_setOffset(long *gyroOffset, long *accelOffset) {
    dmp_set_gyro_bias(gyroOffset);
    dmp_set_accel_bias(accelOffset);
}

static unsigned short inv_row_2_scale(const signed char *row) {
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

static unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx) {
    unsigned short scalar;
    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;
    return scalar;
}

void run_self_test(void) {
    int result;
    long gyro[3], accel[3];
		
    result = mpu_run_self_test(gyro, accel);
    if (result == 0x3) {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        dmp_set_accel_bias(accel);
        printf("setting bias succesfully ...... \r\n");
        printf("#define XG %ld\n", gyro[0]);
        printf("#define YG %ld\n", gyro[1]);
        printf("#define ZG %ld\n", gyro[2]);
        printf("#define XA %ld\n", accel[0]);
        printf("#define YA %ld\n", accel[1]);
        printf("#define ZA %ld\n", accel[2]);
    }
}

/**************************实现函数********************************************
 * void MPU6050_setClockSource(uint8_t source)
 * CLK_SEL | Clock Source
 * --------+--------------------------------------
 * 0       | Internal oscillator
 * 1       | PLL with X Gyro reference
 * 2       | PLL with Y Gyro reference
 * 3       | PLL with Z Gyro reference
 * 4       | PLL with external 32.768kHz reference
 * 5       | PLL with external 19.2MHz reference
 * 6       | Reserved
 * 7       | Stops the clock and keeps the timing generator in reset
*******************************************************************************/
void MPU6050_setClockSource(uint8_t source) {
    IICwriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}

/** Set full-scale gyroscope range.
 * @param range New full-scale gyroscope range value
 * @see getFullScaleRange()
 * @see MPU6050_GYRO_FS_250
 * @see MPU6050_RA_GYRO_CONFIG
 * @see MPU6050_GCONFIG_FS_SEL_BIT
 * @see MPU6050_GCONFIG_FS_SEL_LENGTH
 */
void MPU6050_setFullScaleGyroRange(uint8_t range) {
    IICwriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

void MPU6050_setFullScaleAccelRange(uint8_t range) {
    IICwriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

void MPU6050_setSleepEnabled(uint8_t enabled) {
    IICwriteBit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}

void MPU6050_setI2CMasterModeEnabled(uint8_t enabled) {
    IICwriteBit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_EN_BIT, enabled);
}

void MPU6050_setI2CBypassEnabled(uint8_t enabled) {
    IICwriteBit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_I2C_BYPASS_EN_BIT, enabled);
}

void MPU6050_Init(void) {
    MPU6050_setClockSource(MPU6050_CLOCK_PLL_YGYRO); //设置时钟
    MPU6050_setFullScaleGyroRange(MPU6050_GYRO_FS_2000);//陀螺仪最大量程 +-1000度每秒
    MPU6050_setFullScaleAccelRange(MPU6050_ACCEL_FS_2);	//加速度度最大量程 +-2G
    MPU6050_setSleepEnabled(0); //进入工作状态
    MPU6050_setI2CMasterModeEnabled(0);	 //不让MPU6050 控制AUXI2C
    MPU6050_setI2CBypassEnabled(0);	 //主控制器的I2C与	MPU6050的AUXI2C	直通。控制器可以直接访问HMC5883L
		
}

void MPU6050_DMP_Init(void) {
    uint8_t temp[1]={0};
    i2cRead(0x68, 0x75, 1, temp);
    if (temp[0] != 0x68)
        NVIC_SystemReset();
    if (!mpu_init()) {
        if (!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
            printf("mpu_set_sensor complete ......\r\n");
        if (!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))
            printf("mpu_configure_fifo complete ......\r\n");
        if (!mpu_set_sample_rate(DEFAULT_MPU_HZ))
            printf("mpu_set_sample_rate complete ......\r\n");
        if (!dmp_load_motion_driver_firmware())
            printf("dmp_load_motion_driver_firmware complete ......\r\n");
        if (!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))
            printf("dmp_set_orientation complete ......\r\n");
        if (!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP | DMP_FEATURE_ANDROID_ORIENT |
                                DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL))
            printf("dmp_enable_feature complete ......\r\n");
        if (!dmp_set_fifo_rate(DEFAULT_MPU_HZ))
            printf("dmp_set_fifo_rate complete ......\r\n");
        run_self_test();
        if (!mpu_set_dmp_state(1))
            printf("mpu_set_dmp_state complete ......\r\n");
    }
}

uint8_t MPU6050_getDeviceID(void) {
    uint8_t *buffer;
    IICreadBytes(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I, 1, buffer);
    return *buffer;
}

uint8_t MPU6050_testConnection(void) {
    if (MPU6050_getDeviceID() == 0x68)
        return 1;
    return 0;
}
