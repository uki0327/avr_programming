/*
 * deboucing.c
 *
 * Created: 2020-12-08 오후 6:54:26
 * Author : PROCESSOR
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#define F_CPU  16000000L

void INIT_PORT(void) {
	DDRB = 0x20;
	PORTB = 0x00;
	
	DDRD = 0x00;
	PORTD = 0x04;
}

int main(void)
{
	UART_INIT();
	INIT_PORT();
	int state = 0;
	    
    while (1) 
    {
		if(PIND & 0x04) {
			state = 0;
			PORTB = 0x00;
		} else {
			if(state == 0) UART_transmit('*');
			state = 1;
			PORTB = 0x20;
			_delay_ms(100);
		}
    }
	
	return 1;
}
