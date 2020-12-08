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
#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit)))
#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))

void INIT_PORT(void) {
	DDRB = 0x20;
	PORTB = 0x00;
	
	DDRD = 0x00;
	PORTD = 0x04;
}

unsigned char button_pressed(void) {
	if(bit_is_clear(PIND, PIND2)) { // 첫번째 검사
		_delay_ms(10);
		if(bit_is_clear(PIND, PIND2)) { // 두번째 검사
			return 1;
		}
	}
	return 0;
}



int main(void)
{
	UART_INIT();
	INIT_PORT();
	int state = 0;
	
	while (1)
	{
		if(button_pressed()) {
			if(state == 0) UART_transmit('*');
			state = 1;
			PORTB = 0x20;
			} else {
			state = 0;
			PORTB = 0x00;
		}
	}
	return 1;
}
