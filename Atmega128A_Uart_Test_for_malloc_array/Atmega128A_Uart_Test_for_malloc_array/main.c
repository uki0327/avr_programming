/*
 * Atmega128A_Uart_Test_for_malloc_array.c
 *
 * Created: 2020-12-23 오전 11:50:43
 * Author : PROCESSOR
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART_malloc.h"


int main(void)
{
    UART_INIT(9600, 2);
    while (1) 
    {
		unsigned long a = 728961;
		UART_printNumber(a,10,0,0);
		UART_printString("  ");
		UART_printNumber(a, 16, 1, 1);
		UART_transmit('\n');

		_delay_ms(1000);
    }
}

