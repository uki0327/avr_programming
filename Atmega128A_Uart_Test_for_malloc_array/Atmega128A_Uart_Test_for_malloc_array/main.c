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
		UART_printNumber(125, 8, 2, 1, 1);
		_delay_ms(500);
    }
}

