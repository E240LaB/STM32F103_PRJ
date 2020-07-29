#include "system_init.h"
#include "Transmitter_STM32.h"
u8 Flag_5ms;

int EXTI9_5_IRQHandler(void) 
{    
	if(INT==0)		
	{     
		EXTI->PR=1<<5;                                                       
//		Flag_5ms=!Flag_5ms;
//		if(Flag_5ms==1){
			if(fabs(Angle_Roll)<20){	
				MPU6050_readDMP(); 
				Get_Robot_Position();
				Robot_cmd();
				controlMethod();
				Motion_Transfer(balance_x_control,balance_y_control,steer_control);
				Robot_power_out(motor_A,motor_B,motor_C,motor_D);
				Led_Flash(100);  
			}else{
				Motor_stop();
				delay_ms(10000);
			}
//		}  
		
		
	}
	return 0;	 
} 



void USART2_IRQHandler(void)
{	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 
	{	       
		recvData(USART2,&Angle_KP,&Angle_Rate_KD,&Postion_y_KP, &Velocity_y_KD);
  }
	
}