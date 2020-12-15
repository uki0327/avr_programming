/*
* pwm_using_highspeed_pwm.c
*
* Created: 2020-12-11 오후 10:16:46
* Author : justin
*/
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<PB1);
	
	TCCR1A |= (1 << WGM21) | (1 << WGM20);
	TCCR1A |= (1 << COM2A1);
	TCCR1B |= (1 << CS22);
	
	while (1)
	{
		for(int i = 0; i < 256; i++) {
			OCR1A = i;
			_delay_ms(10);
		}
	}
}

