#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H	  
#include <stm32f10x.h>   
#define SYSTEM_SUPPORT_UCOS		0	
//SYSTEM
#include "delay.h"
#include "usart.h"
//HARDWARE
#include "usartx.h"
#include "motor.h"
#include "encoder.h"
#include "ioi2c.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "led.h"
#include "PWM.h"
#include "test_OLED.h"
//USER_UI
#include "controlLaw.h"
#include "test_fuction.h"
#include "input.h"
#include "output.h"
//closelib
//#include "adc.h"
#include "key.h"
//#include "oled.h"
//#include "show.h"					
//#include "DataScope_DP.h"
#include "stmflash.h" 
//#include "control.h"
#include "filter.h"
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
	
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO¿ÚµØÖ·Ó³Éä
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO¿Ú²Ù×÷,Ö»¶Ôµ¥Ò»µÄIO¿Ú!
//È·±£nµÄÖµÐ¡ÓÚ16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //Êä³ö 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //ÊäÈë 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //Êä³ö 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //ÊäÈë 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //Êä³ö 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //ÊäÈë 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //Êä³ö 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //ÊäÈë 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //Êä³ö 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //ÊäÈë

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //Êä³ö 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //ÊäÈë

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //Êä³ö 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //ÊäÈë


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



