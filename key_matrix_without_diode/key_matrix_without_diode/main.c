/*
* key_matrix_without_diode.c
*
* Created: 2021-01-03 오전 1:20:29
* Author : justin
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

#define ROWS 4
#define COLS 4

char keys[ROWS][COLS] = {
	{
		'1','2','3','A'
		}, {
		'4','5','6','B'
		}, {
		'7','8','9','C'
		}, {
		'*','0','#','D'
	}
};

uint8_t rowPins[ROWS] = {PB1,PB0,PD7,PD6};
uint8_t colPins[COLS] = {PD5,PD4,PD3,PD2};

void InitKeyMatrix(void) {
	DDRB &= ( ~(1 << PB1) & ~(1 << PB0));
	PORTB |= ( (1 << PB1) | (1 << PB0));
	DDRD &= ( ~(1 << PD7) & ~(1 << PD6));
	PORTD |= ( (1 << PD7) | (1 << PD6));
	
	DDRD = 0b11000011; // cols
}

int main(void)
{
	uint8_t keyPressed[ROWS][COLS];
	uint8_t row,col,count;
	
	UART_init_set(115200, 1);
	InitKeyMatrix();
	
	while (1)
	{
		count = 0;
		
		for (col = 0; col < COLS; col++) {
			DDRD |= (1 << colPins[col]);
			PORTD  &= ~(1 << colPins[col]);
			_delay_ms(3);
			
			keyPressed[0][col] = 1 - ((PINB & (1 << rowPins[0])) >> rowPins[0]);
			keyPressed[1][col] = 1 - ((PINB & (1 << rowPins[1])) >> rowPins[1]);
			keyPressed[2][col] = 1 - ((PIND & (1 << rowPins[2])) >> rowPins[2]);
			keyPressed[3][col] = 1 - ((PIND & (1 << rowPins[3])) >> rowPins[3]);
			
			for (row = 0; row < ROWS; row++) {
				count += keyPressed[row][col];
			}
			
			PORTD |= (1 << colPins[col]);
			DDRD &= ~(1 << colPins[col]);
		}
		
		if(count > 0) {
			for(row = 0; row < ROWS; row++) {
				for(col = 0; col < COLS; col++) {
					if(keyPressed[row][col])
						UART_transmit(keys[row][col]);
					else UART_transmit('.');
					
					UART_printString(" ");
				}
				UART_transmit('\n');
			}
			UART_transmit('\n');
		}
		_delay_ms(300);
	}
}

