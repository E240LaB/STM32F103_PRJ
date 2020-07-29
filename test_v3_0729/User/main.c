#include "stm32f10x.h"
#include "system_init.h" 

#define TEST_MODE
#define USER_OFFSET

#ifdef USER_OFFSET

#define XG -3255728
#define YG -1122727
#define ZG 254970
#define XA 16515072
#define YA 20348928
#define ZA -56901632

long gyroOffset[3] = {XG, YG, ZG}, accelOffset[3] = {XA, YA, ZA};
#endif



//================================= TEST_MODE
float errorA = 0,errorB = 0,errorC = 0,errorD = 0;
float thetaA_cmd = 1550, thetaB_cmd=1550, thetaC_cmd=1550, thetaD_cmd=1550;	


//================================= motor 
volatile int thetaA = 0, thetaB=0, thetaC=0, thetaD=0;
volatile int denA = 0,denB = 0,denC = 0,denD = 0;
volatile int othetaA = 0,othetaB = 0,othetaC = 0,othetaD = 0;
volatile int motor_A = 0,motor_B = 0,motor_C = 0,motor_D = 0;
volatile float Robot_Diff_angle = 0.0,
	             Robot_Position_x = 0.0,Robot_Velocity_x = 0.0,
               Robot_Position_y = 0.0,Robot_Velocity_y = 0.0;


	
//================================= mpu6050
volatile float Angle_Pitch = 0.0,Gyro_Pitch = 0.0,
	             Angle_Roll = 0.0,Gyro_Roll = 0.0,
               Angle_Yaw = 0.0,Gyro_Yaw = 0.0;

unsigned int running_count = 0.0;
//================================= control
volatile float Angle_KP = 956.0,Angle_Rate_KD = 370.0,
               Postion_y_KP = 0.67,Velocity_y_KD = 0.34,
			         Diff_angle_KP = 0.54,
							 Postion_x_KP = 0.0;

volatile float balance_y_control = 0.0,steer_control= 0.0,balance_x_control = 0.0,
			         _postion_y = 0.0,postion_y_cmd = 0.0,postion_y_error = 0.0,
							 _postion_x = 0.0,postion_x_cmd = 0.0,postion_x_error = 0.0,
               _Diff_angle = 0.0,Robot_Diff_angle_cmd = 0.0,Robot_Diff_angle_error = 0.0;

int main(void)
{ 
	delay_init();	    	        //=====delay init
	JTAG_Set(SWD_ENABLE);           //=====swd init
	uart3_init(115200);             //=====UART3 init
	uart2_init(115200);
	LED_Init();                     //=====LED init
	IIC_Init();  	//=====IIC init

	//MY_NVIC_PriorityGroupConfig(2);	//=====set init group
	
	MiniBalance_PWM_Init(7199,0); 
	
  MPU6050_Init();
	MPU6050_DMP_Init();
	MPU6050_Interrupt_Init();
	
	#ifdef USER_OFFSET
    MPU6050_setOffset(gyroOffset, accelOffset);
	#endif
	
  
//	OLED_SHOW_INIT();    //=====OLED  init   
	

	Encoder_Init_TIM2();            //===== moterA ENCODER
	Encoder_Init_TIM3();            //===== moterB ENCODER
	Encoder_Init_TIM4();            //===== moterC ENCODER
	Encoder_Init_TIM5();			      //===== moterD ENCODER
              
	

	while(1)
	{
		
		#ifdef TEST_MODE
		//	test_uart();
		//  test_pwm();
		//=================================
		// test_display_UARTENCODER
		// mode 0 ENCODER display
		// mode 1 4 motor P contorller
		// mode 2 moition display
		//=================================
		test_display_UARTENCODER(3);
		//test_motion();
		//test_display_MPU6050_DMP();
		//OLED_SHOW_Info();
		#endif
	} 
}
  




