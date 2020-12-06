#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect) {
	TCNT1 = 0;
}

int main(void) {
	TCCR1B |= (1 << CS12) | (1 << CS00);
	
	OCR1A = 0x2000;
	
	TCCR1A |= (1 << COM1A0);
	
	DDRB |= (1 << PB1); // PB1 = OC1A 핀을 출력으로 설정
	
	TIMSK1 |= (1 << OCIE1A);
	sei();
	
	while(1){ }
}