/*
 * atmega128a_test.c
 *
 * Created: 2020-12-09 오후 6:10:10
 * Author : PROCESSOR
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

int main(void)
{
    UART_INIT(115200);
	
    while (1) 
    {
		UART_printString("바이너리 8비트: ");
		UART_print8bitBinaryInc0f((unsigned int)1);
		UART_transmit('\n');
		UART_printString("바이너리 16비트: ");
		UART_print16bitBinaryInc0f((uint16_t)0b0000000000000001);
		UART_transmit('\n');
		UART_printString("헥스 8비트: ");
		UART_print8bitHexInc0f((unsigned int)0x0D);
		UART_transmit('\n');
		UART_printString("헥스 16비트: ");
		UART_print16bitHexInc0f((uint16_t)0x0AAA);
		UART_printString("\n\n");		
		
		_delay_ms(1000);
    }
}

