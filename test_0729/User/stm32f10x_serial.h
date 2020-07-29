/*#ifndef _SERIAL_H_
#define _SERIAL_H_ 
#ifndef __USART_H
#define __USART_H*/

#include "stm32f10x.h" 
#include "stdio.h"

#define SERIAL1 1
#define SERIAL2 2
#define SERIAL3 3

int fputc(int data, FILE *file);  // Override stdio function "printf"
int fgetc(FILE *file);            // Override stdio function "scanf"

void serialBegin(uint8_t serial, uint32_t baudrate);
void serialWrite(uint8_t serial, char *string);

/*void serial1Init(uint32_t baudrate);
void serial2Init(uint32_t baudrate);
void serial3Init(uint32_t baudrate);*/

void serial1Write(char *string);
void serial2Write(char *string);
void serial3Write(char *string);


/*#endif
#endif*/

