#ifndef __ENCODER_H
#define __ENCODER_H
#include "system_init.h"  

#define ENCODER_TIM_PERIOD (u16)(65535)    //because of F103 Timer is 16 bit, the number cant bigger than 65535
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM3(void);
void Encoder_Init_TIM4(void);
void Encoder_Init_TIM5(void);
int Read_Encoder(u8 TIMX);

void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
#endif
