/*
 * codevisiontest.c
 *
 * Created: 2020-12-08 ¿ÀÀü 11:00:36
 * Author: PROCESSOR
 */
                                       
#define F_CPU 16000000L
#include <mega328p.h>
#include <delay.h>

void main(void)
{
    DDRD = 0xFF;
    PORTD = 0xFF;
while (1)
    {
        PORTD = 0x00;
        delay_ms(500);
        PORTD = 0xFF;
        delay_ms(500);
    }
}
