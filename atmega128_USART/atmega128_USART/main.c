/*
 * atmega128_USART.c
 *
 * Created: 2020-12-15 오전 10:54:35
 * Author : PROCESSOR
 */ 
#define F_CPU 16000000L
#include <avr/io.h>

void Putch(char data);

void main(void) {
	// 전송 문자열
	char string[] = "This is USART1 control program!\n";
	char *pStr;
	
	UCSR1A = 0x00;
	UCSR1B = 0b00001000;
	UCSR1C = 0b00000110;
	UBRR1H = 0;
	UBRR1L = 103;
	pStr = string;
	while(*pStr != 0) Putch(*pStr++);
	
	while(1);
}

void Putch(char data) {
	while((UCSR1A & 0x20) == 0x00);
	
	UDR1 = data;
}
