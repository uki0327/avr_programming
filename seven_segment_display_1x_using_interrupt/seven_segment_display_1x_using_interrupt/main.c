/*
 * seven_segment_display_1x.c
 *
 * Created: 2020-12-31 오전 1:56:48
 * Author : justin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>						
#include <avr/interrupt.h>

volatile int interrupt_count = 0;	

ISR(TIMER0_OVF_vect) {
	interrupt_count++;
}

int main(void)
{
    uint8_t numbers[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
	int count = 0;
	DDRD = 0xFF;
	PORTD = numbers[0];
	
	TCCR0B |= (1 << CS02) | (1 << CS00);
	TIMSK0 |= (1 << TOIE0);
	sei();
	
    while (1) 
    {
		if (interrupt_count == 61) {
			interrupt_count = 0;
			
			count = (count + 1) % 10;
			PORTD = numbers[count];
		}
    }
	
	return 1;
}

