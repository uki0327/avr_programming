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
	int count = 0;
	DDRD = 0xFF;
	
    while (1) 
    {
		PORTD = numbers[count];
		//PORTD = 0xFC;
		count = (count + 1) % 10;
		
		_delay_ms(1000);
    }
	
	return 1;
}

