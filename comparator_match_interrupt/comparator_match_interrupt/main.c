#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000L

int count = 0;
int state = 0;

ISR(TIMER0_COMPA_vect) {
	count++;
	TCNT0 = 0;
	if(count==32) {
		count = 0;
		state = !state;
		if(state) PORTD = 0x00;
		else PORTD = 0xFF;
	}
}

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;
	
	TCCR0B |= (1 << CS02) | (1 << CS00);
	
	OCR0A = 128;
	
	TIMSK0 |= (1 << OCIE0A);
	sei();
	
	while (1)
	{
		
	}
}

