#ifndef _TRANSMITTER_H_
#define _TRANSMITTER_H_

#include "stm32f10x.h"

void sendByte(USART_TypeDef *USARTx, const unsigned char nValue);
void sendFloat(USART_TypeDef *USARTx, const float nValue);
float readFloat(const unsigned char nIndex);
void sendData(USART_TypeDef *USARTx, const unsigned char nLength, ...);
void recvData(USART_TypeDef *USARTx, float *k1, float *k2, float *k3, float *k4);

#endif
