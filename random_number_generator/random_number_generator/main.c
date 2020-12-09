/*
* ADC_potentiometer_led_count.c
*
* Created: 2020-12-08 오후 8:19:41
* Author : PROCESSOR
*/
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include <stdlib.h>

void ADC_INIT(unsigned char channel) {
	ADMUX |= 0x40;
	
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADATE);
	
	ADMUX |= ((ADMUX & 0xE0) | channel);
	ADCSRA |= (1 << ADSC);
}

int read_ADC(void) {
	while(!(ADCSRA & (1 << ADIF)));
	
	return ADC;
}


int main(void)
{
	UART_INIT();
	ADC_INIT(0);
	srand(read_ADC());
	
	UART_printString("** Start generating random number...\n");
	
	while(1) {
		int randomNumber = rand() %100 + 1;
		
		UART_print8bitNumber(randomNumber);
		UART_transmit('\r\n');
		
		_delay_ms(1000);
	}
	
	return 1;
}


