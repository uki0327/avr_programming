/*
* ADC_potentiometer_led_count.c
*
* Created: 2020-12-08 오후 8:19:41
* Author : PROCESSOR
*/
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
//#include "UART.h"
//#include <stdio.h>

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

void PORT_INIT(void) {
	DDRD = 0xFF;
	PORTD = 0xFF;
}
int main(void)
{
	int value;
	uint8_t on_off;
	
	ADC_INIT(0);
	PORT_INIT();
	//UART_INIT();
	
	while (1)
	{
		value = read_ADC() >> 7;
		
		on_off = 0;
		for(int i = 0; i <= value ; i++) {
			on_off |= (0x01 << i);
		}
		
		PORTD = ~on_off;
		
		//char on_off_str[10];
		//sprintf(on_off_str, "%d", on_off);
		//UART_printString("PORTD : ");
		//UART_printString(on_off_str);
		//UART_printString("\n");
	}
	
}


