#ifndef __USART_H
#define __USART_H
#include "system_init.h"
#include "stdio.h"	

void usart2_send(u8 data);
void uart2_init(u32 bound);
void USART2_IRQHandler(void);
u8 click_RC (void);
void USART_TX(void);

extern char state;

#endif	   
















