#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "PWM.h"

#define PWM_ARR     7200
#define PWM_LIMIT   PWM_ARR

void Motor_PWM_PWM_A(float power) 
{
	if(power>0)			 PWMA1=7200,PWMA2=7200-power;
	else 	            PWMA2=7200,PWMA1=7200+power;

}

void Motor_PWM_PWM_B(int power) 
{
	if(power>0)		    PWMB2=7200,PWMB1=7200-power;
	else 	            PWMB1=7200,PWMB2=7200+power;
}
void Motor_PWM_PWM_C(int power) 
{
	if(power>0)		    PWMC1=7200,PWMC2=7200-power;
	else 	            PWMC2=7200,PWMC1=7200+power;
	
}
void Motor_PWM_PWM_D(int power) 
{
    if(power>0)	    PWMD1=7200,PWMD2=7200-power;
	else 	            PWMD2=7200,PWMD1=7200+power;

}


void Motor_stop(void)
{
	Motor_PWM_PWM_A(0);
	Motor_PWM_PWM_B(0);
	Motor_PWM_PWM_C(0);
	Motor_PWM_PWM_D(0);
}


