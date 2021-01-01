/*
 * lex_matrix_drawing_smile.c
 *
 * Created: 2021-01-02 오전 12:45:21
 * Author : justin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LEDMatrix.h"


int main(void)
{
    LEDMatrix_init();
	
	uint8_t smile[] = {
		0b00111100,
		0b01000010,
		0b10100101,
		0b10000001,
		0b10100101,
		0b10011001,
		0b01000010,
		0b00111100
	};
	
    while (1) 
    {
		for(int i = 0; i < 8; i++) {
			LEDMatrix_writeRow(0);
			
			uint8_t col_data = ~(1 << i);
			LEDMatrix_writeColumn(col_data);
			
			LEDMatrix_writeRow(smile[i]);
			
			_delay_ms(2);
		}
		
    }
}

