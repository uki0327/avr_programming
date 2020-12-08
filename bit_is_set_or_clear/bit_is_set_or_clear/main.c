/*
 * bit_is_set_or_clear.c
 *
 * Created: 2020-12-08 오후 7:28:23
 * Author : PROCESSOR
 */ 

#include <avr/io.h>
#define bit_is_set(sfr, bit) (_SFR_BYTE(sfr) & _BV(bit)))
#define bit_is_clear(sfr, bit) (!(_SFR_BYTE(sfr) & _BV(bit)))

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

