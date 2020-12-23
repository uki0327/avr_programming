/*
 * UART.h
 *
 * Created: 2020-12-08 오후 3:01:33
 *  Author: PROCESSOR
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void UART_INIT(unsigned long baud, char x);
unsigned char UART_receive(void);
void UART_transmit(unsigned char data);
void UART_printString(char *str);
void UART_printNumber(unsigned long number, unsigned char bit, unsigned char numeral, unsigned char zero, unsigned char format);
unsigned char getStringArrayNum(unsigned char bit, unsigned char numeral);

#endif /* UART_H_ */