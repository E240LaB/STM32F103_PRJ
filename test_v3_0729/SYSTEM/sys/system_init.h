#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H	  
#include <stm32f10x.h>   
//SYSTEM
#include "delay.h"
#include "usart.h"
//HARDWARE
#include "usartx.h"
#include "motor.h"
#include "test_OLED.h"
#include "encoder.h"
#include "ioi2c.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "led.h"
#include "PWM.h"
//USER_UI
#include "controlLaw.h"
#include "test_fuction.h"
#include "input.h"
#include "output.h"
//closelib
//#include "adc.h"
//#include "key.h"
//#include "show.h"					
//#include "DataScope_DP.h"
//#include "stmflash.h" 
//#include "spi.h"
//#include "24l01.h"   
//#include "can.h"
//#include "pstwo.h"
//#include "timer.h"
//////////////////////////////////////////////////////////////////////////////
#include <string.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/////////////////////////////////////////////////////////////////
#define SYSTEM_SUPPORT_UCOS		0		

#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	

#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 

#define FTIR   1  
#define RTIR   2  

//add mpu6050 20200721
#define INT PCin(5) //add mpu6050 20200721
/////////////////////////////////////////////////////////////////  
void Stm32_Clock_Init(u8 PLL);   
void Sys_Soft_Reset(void);      
void Sys_Standby(void);          	
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//�����ж�
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);
void JTAG_Set(u8 mode);
//////////////////////////////////////////////////////////////////////////////

void WFI_SET(void);		
void INTX_DISABLE(void);
void INTX_ENABLE(void);	
void MSR_MSP(u32 addr);	
//////////////////////////////////////////////////////////////////////////////

//mpu6050_interrup   
extern u8 delay_50,delay_flag; 
extern u8 Run_Flag; 
extern u8 Flag_5ms;
//extern u8 rxbuf[8],Urxbuf[8],CAN_ON_Flag,Usart_ON_Flag,Usart_Flag,PID_Send; 
//extern u8 txbuf[8],txbuf2[8];  

//dmp_data
extern volatile float Angle_Pitch,Angle_Roll,Angle_Yaw,Gyro_Pitch,Gyro_Roll,Gyro_Yaw;   


//ps2
extern volatile int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY; 
extern u16 CCD_Zhongzhi,CCD_Yuzhi,ADV[128];

// motor 
extern volatile int thetaA, thetaB, thetaC, thetaD;
extern volatile int denA,denB,denC,denD;
extern volatile int othetaA,othetaB,othetaC,othetaD;
extern volatile float Robot_Diff_angle,Robot_Position_x,Robot_Velocity_x,Robot_Position_y,Robot_Velocity_y;
extern volatile int motor_A,motor_B,motor_C,motor_D;

//test_function
extern float errorA,errorB,errorC,errorD ;
extern float thetaA_cmd,thetaB_cmd,thetaC_cmd,thetaD_cmd;	

//control
extern volatile float Angle_KP,Angle_Rate_KD ,
											Postion_y_KP,Velocity_y_KD,
											Diff_angle_KP,
											Postion_x_KP;
extern volatile float balance_y_control,steer_control,balance_x_control,
			         _postion_y,postion_y_cmd,postion_y_error,
							 _postion_x,postion_x_cmd,postion_x_error,
               _Diff_angle,Robot_Diff_angle_cmd,Robot_Diff_angle_error;

extern void (*controlMethod)(void);

extern unsigned int running_count;
//
typedef union {
    char byteVal[4];
    float floatVal;
} VAL;
#endif



