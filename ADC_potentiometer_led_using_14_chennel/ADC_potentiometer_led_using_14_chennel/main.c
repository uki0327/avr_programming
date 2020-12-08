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
#include <stdio.h>

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
	int read, alctualVCC;
	
	ADC_INIT(14);
	UART_INIT();
	
	while (1)
	{
		read = read_ADC();
		alctualVCC = 1125300L / read;
		
		UART_printString("actualVCC = ");
		UART_print16bitNumber(alctualVCC);
		UART_printString("\n");
		
		_delay_ms(1000);
	}
	
	return 1;	
}


