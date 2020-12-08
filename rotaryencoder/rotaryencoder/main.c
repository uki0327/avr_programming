/*
* rotaryencoder.c
*
* Created: 2020-12-08 오후 12:34:51
* Author : PROCESSOR

	LEDs on PORTD, Rotary Encoder Button on PB5,
	Rotary Encoder A and B on PB0 and PB1,
	Using PCINT (Pin Change Interrupt) on PORTB,
	shouldn't use UART for LEDs on PD0 and PD1 (RX and TX Pins)
*/

#include <avr/io.h>
#include <avr/interrupt.h>
//#include "UART.h"
#include <stdio.h>

#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0

int led_on = 0xFE;
int clk = 0;
int oldA = 0;
int oldB = 0;

void INIT_PCINT0();
void ledShift(int c);


int main(void)
{
	DDRD = 0xFF;		// LEDs
	DDRB = 0x00;		// BUTTON
	
	PORTD = 0xFE;		// STARTS with the First LED ON
	PORTB = 0xFF;		// BUTTON PULLUP
	
	//UART_INIT();
	INIT_PCINT0();
	
	while (1)
	{
	}
	return 0;
}


void INIT_PCINT0() {
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1<< PCINT0) | (1<< PCINT1) | (1 << PCINT5);
	sei();
}


void ledShift(int c) {
	if(clk == CLOCKWISE) {					// 시계방향으로 1 비트 이동
		if (c == 1) ledLeft();
		else ledRight();

		} else if (clk == COUNTERCLOCKWISE) {		// 반시계방향 1비트 이동
		if (c == 1) ledRight();
		else ledLeft();
		
	}
}

void ledLeft() {
	// +1
	if (led_on == 0b01111111) {
		led_on = 0b11111110;
		PORTD = led_on;
	}
	else {
		led_on = (led_on << 1) + 1;
		led_on = ~(1 << 8) & led_on;
		PORTD = led_on;
	}

	//UART_printString("\nShift 1 bit to LEFT\n");

}

void ledRight() {		// -1
	if(led_on == 0b11111110) {
		led_on = 0b01111111;
		PORTD = led_on;
	}
	else {
		led_on = 0b10000000 | (led_on >> 1);
		PORTD =  led_on;
	}
	
	//UART_printString("\nShift 1 bit to RIGHT\n");
}

ISR(PCINT0_vect)
{

	int newA = 1 & PINB;
	int newB = 1 & (PINB >> 1);
	
	if(oldA != newA)  {									// A 가 변화
		if(newA == 1) {
			if(newB == 1) ledShift(0);
			else ledShift(1);
		}
		else {
			if(newB == 1) ledShift(1);
			else ledShift(0);
		}
	}
	
	if(oldB != oldB) {
		if(newB == 1) {
			if(newA == 1) ledShift(1);
			else ledShift(0);
		}
		else {
			if(newA == 1) ledShift(0);
			else ledShift(1);
		}
	}
	
	if ((1 & (PINB >> PB5)) == 0) {
		clk = !clk;				// 엔코더 회전 방향 바꾸기
	}
	
	oldA = newA;
	oldB = newB;
}