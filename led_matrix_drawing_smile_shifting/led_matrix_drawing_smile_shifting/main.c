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

uint8_t smile_shifted[8];


void smile_shifting(char dir, char shifting) {
	for (int i = 0; i < 8; i++) {
		if(dir == 1) smile_shifted[i] = smile[i] >> shifting;
		else if(dir == 0) smile_shifted[i] = smile[i] << shifting;
	}
}


int main(void)
{
    LEDMatrix_init();
	int count = 0;
	
    while (1) 
    {
		if (count < 100) smile_shifting(1, 0);
		else if(count >= 100 && count < 200) smile_shifting(0, 1);
		else if(count >= 200 && count < 300) smile_shifting(0, 2);
		else if(count >= 300 && count < 400) smile_shifting(0, 3);
		else if(count >= 400 && count < 500) smile_shifting(0, 4);
		else if(count >= 500 && count < 600) smile_shifting(0, 3);
		else if(count >= 600 && count < 700) smile_shifting(0, 2);
		else if(count >= 700 && count < 800) smile_shifting(0, 1);
		else if(count >= 800 && count < 1100) smile_shifting(1, 0);
		else if(count >= 1100 && count < 1200) smile_shifting(1, 1);
		else if(count >= 1200 && count < 1300) smile_shifting(1, 2);
		else if(count >= 1300 && count < 1400) smile_shifting(1, 3);
		else if(count >= 1400 && count < 1500) smile_shifting(1, 4);
		else if(count >= 1500 && count < 1600) smile_shifting(1, 3);
		else if(count >= 1600 && count < 1700) smile_shifting(1, 2);
		else if(count >= 1700 && count < 1800) smile_shifting(1, 1);
		else if(count >= 1800 && count < 2000) smile_shifting(1, 0);
		else if(count >= 2000) count = 0;
		
		for(int i = 0; i < 8; i++) {
			LEDMatrix_writeRow(0);
			
			uint8_t col_data = ~(1 << i);
			LEDMatrix_writeColumn(col_data);
			
			LEDMatrix_writeRow(smile_shifted[i]);
			
			_delay_ms(2);
			count++;
		}
		
    }
}

