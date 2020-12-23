/*
 * Hardware_Serial_Test_128A.c
 *
 * Created: 2020-12-22 오후 12:15:05
 * Author : PROCESSOR
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "UART_USE_1.h"

int main(void)
{
	unsigned char data;
	
	UART_INIT(9600,2);
	
    while (1) 
    {
		data = UART_receive();
		UART_transmit(data);
    }
	
	return 0;
}

