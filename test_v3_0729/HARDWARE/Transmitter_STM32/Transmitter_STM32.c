#include "Transmitter_STM32.h"
#include <stdarg.h>

union {
    unsigned char byteValue[4];
    float floatValue;
} unionData;

unsigned char isAvailable = 0,
              nPreByte = 0,
              nCurByte = 0,
              nIndex = 0,
              nLength = 0,
              nStart = 0,
              nBuffer[64];

void sendByte(USART_TypeDef *USARTx, const unsigned char nValue) {
    USARTx->DR = nValue;
    while ((USART1->SR & 0x40) == RESET);
}

void sendFloat(USART_TypeDef *USARTx, const float nValue) {
    unionData.floatValue = nValue;
    sendByte(USARTx, unionData.byteValue[0]);
    sendByte(USARTx, unionData.byteValue[1]);
    sendByte(USARTx, unionData.byteValue[2]);
    sendByte(USARTx, unionData.byteValue[3]);
}

float readFloat(const unsigned char nIndex) {
    unionData.byteValue[0] = nBuffer[nIndex];
    unionData.byteValue[1] = nBuffer[nIndex + 1];
    unionData.byteValue[2] = nBuffer[nIndex + 2];
    unionData.byteValue[3] = nBuffer[nIndex + 3];
    return unionData.floatValue;
}

void sendData(USART_TypeDef *USARTx, const unsigned char nLength, ...) {
    int i;
    va_list nArgs;

    sendByte(USARTx, 0xff);
    sendByte(USARTx, 0x55);
    sendByte(USARTx, nLength * 4);
    va_start(nArgs, nLength);
    for (i = 0; i < nLength; i++) {
        sendFloat(USARTx, (float)va_arg(nArgs, double));
    }
    va_end(nArgs);
}

void recvData(USART_TypeDef *USARTx, float *k1, float *k2, float *k3, float *k4) {
    isAvailable = 0;
    if ((USARTx->SR & 0x20) == SET) {
        isAvailable = 1;
        nCurByte = USARTx->DR;
    }
    if (isAvailable) {
        if (nCurByte == 0x55 && nStart == 0) {
            if (nPreByte == 0xff) {
                nIndex = 1;
                nStart = 1;
            }
        }
        else {
            nPreByte = nCurByte;
            if (nStart == 1) {
                if (nIndex == 2) {
                    nLength = nCurByte;
                }
                else if (nIndex > 2) {
                    nLength--;
                }
                nBuffer[nIndex] = nCurByte;
            }
        }
        nIndex++;
        if (nIndex > 63) {
            nIndex = 0;
            nStart = 0;
        }
        if (nStart == 1 && nLength == 0 && nIndex > 3) {
            nIndex = 0;
            nStart = 0;
            switch (nBuffer[7]) {
                case 0x01: {
                    *k1 = readFloat(3);
                    break;
                }
                case 0x02: {
                    *k2 = readFloat(3);
                    break;
                }
                case 0x03: {
                    *k3 = readFloat(3);
                    break;
                }
                case 0x04: {
                    *k4 = readFloat(3);
                    break;
                }
                case 0x05: {
                    sendData(USARTx, 4, *k1, *k2, *k3, *k4);
                    break;
                }
            }
        }
    }
}
