/*
 * UART.h
 *
 * Created: 2020-12-08 오후 3:01:33
 *  Author: Justin
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void UART_init(void);
void UART_init_set(unsigned long baud, char x);
unsigned char UART_receive(void);
void UART_transmit(unsigned char data);
void UART_printString(char *str);
void UART_print8bitNumber(uint8_t no);
void UART_print16bitNumber(uint16_t no);
void UART_print32bitNumber(uint32_t no);
void UART_print8bitBinaryNumber(uint8_t no);
void UART_print8bitBinaryInc0(uint8_t no);
void UART_print8bitBinaryInc0f(uint8_t no);
void UART_print16bitBinaryNumber(uint16_t no);
void UART_print16bitBinaryInc0(uint16_t no);
void UART_print16bitBinaryInc0f(uint16_t no);
void UART_print8bitHexNumber(uint8_t no);
void UART_print8bitHexInc0(uint8_t no);
void UART_print8bitHexInc0f(uint8_t no);
void UART_print16bitHexNumber(uint16_t no);
void UART_print16bitHexInc0(uint16_t no);
void UART_print16bitHexInc0f(uint16_t no);

#endif /* UART_H_ */