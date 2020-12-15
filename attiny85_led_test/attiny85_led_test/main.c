/*
 * attiny85_led_test.c
 *
 * Created: 2020-12-11 오후 8:54:06
 * Author : justin
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 0xFF;
	DDRB = 0xFF;
	
    while (1) 
    {
		PORTD = 0b01010101;
		PORTB |= (1<<PB0);
		PORTB &= ~(1<<PB1);
		_delay_ms(5);
		PORTD = 0b10101010;
		PORTB |= (1<<PB1);
		PORTB &= ~(1<<PB0);
		_delay_ms(5);
    }
}

