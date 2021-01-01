/*
 * LEDMatrix.h
 *
 * Created: 2021-01-02 오전 12:09:28
 *  Author: justin
 */ 

#ifndef LEDMATRIX_H_
#define LEDMATRIX_H_

// DDR register for row
#define MATRIX_ROW1_DDR	DDRA
#define MATRIX_ROW2_DDR	DDRA
#define MATRIX_ROW3_DDR	DDRA
#define MATRIX_ROW4_DDR	DDRA
#define MATRIX_ROW5_DDR	DDRA
#define MATRIX_ROW6_DDR	DDRA
#define MATRIX_ROW7_DDR	DDRA
#define MATRIX_ROW8_DDR	DDRA

// PORT register for row
#define MATRIX_ROW1_PORT	PORTA
#define MATRIX_ROW2_PORT	PORTA
#define MATRIX_ROW3_PORT	PORTA
#define MATRIX_ROW4_PORT	PORTA
#define MATRIX_ROW5_PORT	PORTA
#define MATRIX_ROW6_PORT	PORTA
#define MATRIX_ROW7_PORT	PORTA
#define MATRIX_ROW8_PORT	PORTA

// pin number for row
#define MATRIX_ROW1_PIN	PA0
#define MATRIX_ROW2_PIN	PA1
#define MATRIX_ROW3_PIN	PA2
#define MATRIX_ROW4_PIN	PA3
#define MATRIX_ROW5_PIN	PA4
#define MATRIX_ROW6_PIN	PA5
#define MATRIX_ROW7_PIN	PA6
#define MATRIX_ROW8_PIN	PA7

// DDR register for column
#define MATRIX_COL1_DDR	DDRC
#define MATRIX_COL2_DDR	DDRC
#define MATRIX_COL3_DDR	DDRC
#define MATRIX_COL4_DDR	DDRC
#define MATRIX_COL5_DDR	DDRC
#define MATRIX_COL6_DDR	DDRC
#define MATRIX_COL7_DDR	DDRC
#define MATRIX_COL8_DDR	DDRC

// PORT register for column
#define MATRIX_COL1_PORT	PORTC
#define MATRIX_COL2_PORT	PORTC
#define MATRIX_COL3_PORT	PORTC
#define MATRIX_COL4_PORT	PORTC
#define MATRIX_COL5_PORT	PORTC
#define MATRIX_COL6_PORT	PORTC
#define MATRIX_COL7_PORT	PORTC
#define MATRIX_COL8_PORT	PORTC

// pin number for column
#define MATRIX_COL1_PIN	PC0
#define MATRIX_COL2_PIN	PC1
#define MATRIX_COL3_PIN	PC2
#define MATRIX_COL4_PIN	PC3
#define MATRIX_COL5_PIN	PC4
#define MATRIX_COL6_PIN	PC5
#define MATRIX_COL7_PIN	PC6
#define MATRIX_COL8_PIN	PC7

#endif /* LEDMATRIX_H_ */

void LEDMatrix_init(void);
void LEDMatrix_writeColumn(uint8_t col_data);
void LEDMatrix_writeRow(uint8_t row_data);