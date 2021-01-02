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
	int count = 0;
	char num = 0;
	
	uint8_t numbers[10][8] = {
		{
			0b00111100,
			0b01000010,
			0b01000010,
			0b01000010,
			0b01000010,
			0b01000010,
			0b01000010,
			0b00111100
			}, {
			0b00001000,
			0b00011000,
			0b00001000,
			0b00001000,
			0b00001000,
			0b00001000,
			0b00001000,
			0b00001000
			}, {
			0b00111100,
			0b01000010,
			0b00000010,
			0b00000100,
			0b00001000,
			0b00010000,
			0b00100000,
			0b01111110
			}, {
			0b00111100,
			0b01000010,
			0b00000010,
			0b00011100,
			0b00000010,
			0b00000010,
			0b01000010,
			0b00111100
			}, {
			0b00001100,
			0b00010100,
			0b00100100,
			0b01000100,
			0b01111110,
			0b00000100,
			0b00000100,
			0b00000100
			}, {
			0b01111110,
			0b01000000,
			0b01000000,
			0b01111100,
			0b00000010,
			0b00000010,
			0b00000010,
			0b01111100
			}, {
			0b00111100,
			0b01000010,
			0b01000000,
			0b01111100,
			0b01000010,
			0b01000010,
			0b01000010,
			0b00111100
			}, {
			0b01111110,
			0b00000010,
			0b00000010,
			0b00000100,
			0b00001000,
			0b00010000,
			0b00100000,
			0b01000000
			}, {
			0b00111100,
			0b01000010,
			0b01000010,
			0b00111100,
			0b01000010,
			0b01000010,
			0b01000010,
			0b00111100
			}, {
			0b00111100,
			0b01000010,
			0b01000010,
			0b00111100,
			0b00000100,
			0b00001000,
			0b00010000,
			0b00100000
		}
	};
	
	while (1)
	{
		if(count >= 500) {
			num = (num + 1) % 10;
			count = 0;
		}
		
		for(int i = 0; i < 8; i++) {
			LEDMatrix_writeRow(0);
			
			uint8_t col_data = ~(1 << i);
			
			LEDMatrix_writeColumn(col_data);
			LEDMatrix_writeRow(numbers[num][i]);
			
			_delay_ms(2);
			count++;
		}
		
	}

}