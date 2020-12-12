/*
* pwm_using_delay.c
*
* Created: 2020-12-11 오후 9:58:55
* Author : justin
*/
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define LED_TIME 20

void turn_on_LED_in_PWM_manner(int dim) {
	int i;
	
	PORTB = 0xFF;
	
	for (i = 0; i<256; i++) {
		if(i>dim) PORTB = 0x00;
		_delay_us(LED_TIME);
	}
}

int main(void)
{
	
	DDRB = 0xFF;
	
	int dim = 0;
	int direction = 1;
	
	while (1)
	{
		if(dim == 0) direction = 1;
		if(dim == 255) direction = -1;
		
		dim += direction;
		
		turn_on_LED_in_PWM_manner(dim);
	}
}

