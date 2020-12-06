#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000L

int count = 0;
int state = 0;

ISR(TIMER0_OVF_vect) {
	count++;
	if(count == 32) {
		count = 0;
		state = !state;
		if(state) PORTD = 0x00;
		else PORTD = 0xFF;
	}
}

int main(void) {
	DDRD = 0x20;
	PORTD = 0x20;
	
	TCCR0B |= (1 << CS02) | (1 << CS00);
	
	TIMSK0 |= (1 << TOIE0);
	sei();
	
	while(1) { }
}