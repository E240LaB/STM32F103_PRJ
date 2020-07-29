#ifndef __MOTOR_H
#define __MOTOR_H
#include "system_init.h"  


/****Motor A****/
#define PWMA2   TIM8->CCR1 //postive
#define PWMA1   TIM1->CCR1 

/****Motor B****/
#define PWMB2   TIM8->CCR2 
#define PWMB1   TIM1->CCR2 //postive

/****Motor C****/
#define PWMC2   TIM8->CCR3
#define PWMC1   TIM1->CCR3 //postive

/****Motor D****/
#define PWMD1   TIM8->CCR4 //postive
#define PWMD2   TIM1->CCR4 

void MiniBalance_PWM_Init(u16 arr,u16 psc);
#endif
