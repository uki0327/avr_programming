/*
 * led_blink.c
 *
 * Created: 2020-12-06 오후 6:23:28
 * Author : justin
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0xFF;
    while (1) 
    {
		for(int i = 0; i< 8; i++) {
			char p1 = 0x01 << i;
			char p2 = 0x01 << (7 - i);
			char f = ~(p1 | p2);
			PORTD = f;
			_delay_ms(500); 
		}

    }
}

