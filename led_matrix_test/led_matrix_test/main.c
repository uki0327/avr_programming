/*
 * led_matrix_test.c
 *
 * Created: 2021-01-01 오후 11:49:01
 * Author : justin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LEDMatrix.h"


int main(void)
{
	LEDMatrix_init();
    
    while (1) 
    {
		for(int i = 0; i < 8; i++) {
			uint8_t col_data = ~(1 << i);
			LEDMatrix_writeColumn(col_data);
			
			for(int j = 0; j < 8; j++) {
				uint8_t row_data = 1 << (7 - j);
				LEDMatrix_writeRow(row_data);
				
				_delay_ms(100);
			}
		}
    }
}

