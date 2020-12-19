/*
* comparator_match_interrupt2.c
*
* Created: 2020-12-06 오후 9:12:12
* Author : justin
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000L

volatile int count = 0;
int state = 0;

ISR(TIMER0_COMPA_vect) {
	count++;
	TCNT0 = 0;
	
}

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;
	
	TCCR0B |= (1 << CS02) | (1 << CS00);
	
	OCR0A = 1;
	
	TIMSK0 |= (1 << OCIE0A);
	sei();
	
	while (1)
	{
		if(count==1) {
			count = 0;
			state = !state;
			if(state) PORTD = 0x00;
			else PORTD = 0xFF;
		}
		
	}
}


