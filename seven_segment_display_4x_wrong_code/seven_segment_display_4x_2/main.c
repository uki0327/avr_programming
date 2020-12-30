/*
 * seven_segment_display_1x.c
 *
 * Created: 2020-12-31 오전 1:56:48
 * Author : justin
 *
 *	4자리 세그먼트가 제대로 표시되지 않는 예제
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SEGMENT_DELAY 5

int main(void)
{
    uint8_t numbers[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
	int count = 1000;
	int thousands, hundreds, tens, ones;
	
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
		
		_delay_ms(100);
		
		count++;
		if(count == 10000) count = 1000;
	}
	
	return 1;
}

