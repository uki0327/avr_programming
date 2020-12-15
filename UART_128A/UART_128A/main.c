/*
* atmega128_USART.c
*
* Created: 2020-12-15 오전 10:54:35
* Author : PROCESSOR
*/
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "UART_128A_USE_1.h"

int main(void) {
	UART_INIT(9600,2);
	UART_printString("Hello there~!\n");
	
	int i = 0;
	
	while(1){
		UART_print8bitNumber(i);
		UART_printString(": Hello there~!\n");
		i++;
		_delay_ms(500);
	}
	
	return 1;
}