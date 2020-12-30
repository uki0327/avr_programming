/*
 * seven_segment_display_1x.c
 *
 * Created: 2020-12-31 오전 1:56:48
 * Author : justin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    uint8_t numbers[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
	int i, j;
	
	DDRD = 0xFF;
	DDRB = 0x0F;
	
    while (1) 
    {
		for (i = 0; i < 4; i++) {
			PORTB = 0x0F & ~(1 << i);
			for (j = 0; j < 10; j++) {
				PORTD = numbers[j];
				_delay_ms(100);
			}
		}
    }
	
	return 1;
}

