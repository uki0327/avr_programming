/*
 * seven_segment_display_4x.c
 *
 * Created: 2020-12-31 오전 1:56:48
 * Author : justin
 *
 * 인터럽트 millis() 이용하여 4자리 세그먼트 표시하기 (delay 사용 안함)
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SEGMENT_DELAY 5

#define CLOCKS_PER_MICRO ( F_CPU / 1000000L )
#define CLOCKS_TO_MICROSECONDS(a) ( (a) / CLOCKS_PER_MICRO )
#define MICROSECONDS_PER_TIMER0_OVERFLOW ( CLOCKS_TO_MICROSECONDS(64 * 256) )
#define MILLIS_INCREMENT_PER_OVERFLOW ( MICROSECONDS_PER_TIMER0_OVERFLOW / 1000 )
#define MICROS_INCREMENT_PER_OVERFLOW ( MICROSECONDS_PER_TIMER0_OVERFLOW % 1000 )

volatile unsigned long timer0_millis = 0;
volatile int timer0_micros = 0;

ISR(TIMER0_OVF_vect) {
	unsigned long m = timer0_millis;
	int f = timer0_micros;
	
	m += MILLIS_INCREMENT_PER_OVERFLOW;
	f += MICROS_INCREMENT_PER_OVERFLOW;
	
	int micro_to_millis = f / 1000;
	m += micro_to_millis;
	f = f % 1000;
	
	timer0_millis = m;
	timer0_micros = f;
}

unsigned long millis() {
	unsigned long m;
	uint8_t oldSREG = SREG;
	
	cli();
	
	m = timer0_millis;
	
	SREG = oldSREG;
	
	return m;
}

int main(void)
{
    uint8_t numbers[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
	int count = 1000;
	int thousands, hundreds, tens, ones;
	
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TIMSK0 |= (1 << TOIE0);
	sei();
	
	unsigned long time_previous, time_current;
	time_previous = millis();
	
	DDRD = 0xFF;
	DDRB = 0x0F;
	
    while (1) 
    {
		thousands = count / 1000;
		hundreds = count / 100 % 10;
		tens = count / 10 % 10;
		ones = count % 10;
		
		PORTB = 0x0E;
		PORTD = numbers[thousands];
		_delay_ms(SEGMENT_DELAY);
		
		PORTB = 0x0D;
		PORTD = numbers[hundreds];
		_delay_ms(SEGMENT_DELAY);
		
		PORTB = 0x0B;
		PORTD = numbers[tens];
		_delay_ms(SEGMENT_DELAY);
		
		PORTB = 0x07;
		PORTD = numbers[ones];
		_delay_ms(SEGMENT_DELAY);
		
		time_current = millis();
		
		if(time_current - time_previous > 100) {
			time_previous = time_current;
			count++;
			if(count == 10000) count - 1000;
		}
	}
	
	return 1;
}

