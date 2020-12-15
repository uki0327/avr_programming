/*
UART.c

Created: 2020-12-08 오후 2:51:06
Author : PROCESSOR
*/
#define F_CPU 16000000L
#include <avr/io.h>
#include "UART_128A_USE_1.h"


void UART_INIT(unsigned long boud, char x) {
	if (x == 2) UCSR1A |= _BV(U2X0); // 비동기 2배속 모드
	else if (x == 1) UCSR1A = 0x00;
	
	UBRR1H = 0x00;
	
	int xFactor = 2;
	if (x == 1) xFactor = 16;	//	비동기 정상(1배속) 모드
	else if (x == 2) xFactor = 8; // 비동기 2배속 모드
	else if (x == 3) xFactor = 2; // 동기 마스터 모드
	
	int UBRRnL_Value = F_CPU / (xFactor * boud) - 1;
	UBRR1L = UBRRnL_Value;
	
	UCSR1C |= 0x06;

	UCSR1B |= _BV(RXEN0);
	UCSR1B |= _BV(TXEN0);
	
}

unsigned char UART_receive(void) {
	while ( !(UCSR1A & (1 << RXC0)));
	return UDR1;
}

void UART_transmit(unsigned char data) {
	while ( !(UCSR1A & (1 << UDRE0)));
	UDR1 = data;
}

void UART_printString(char *str) {
	for (int i = 0; str[i]; i++) {
		UART_transmit(str[i]);
	}
}

void UART_print8bitNumber(uint8_t no) {
	char numString[4] = "0";
	int i, index = 0;

	if (no > 0) {
		for (i = 0; no != 0; i++ ) {
			numString[i] = no % 10 + '0';
			no = no / 10;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print16bitNumber(uint16_t no) {
	char numString[6] = "0";
	int i, index = 0;

	if (no > 0) {
		for (i = 0; no != 0; i++ ) {
			numString[i] = no % 10 + '0';
			no = no / 10;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print32bitNumber(uint32_t no) {
	char numString[11] = "0";
	int i, index = 0;

	if (no > 0) {
		for (i = 0; no != 0; i++ ) {
			numString[i] = no % 10 + '0';
			no = no / 10;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print8bitBinaryNumber(uint8_t no) {
	char numString[8] = "0";
	int i, index = 0;

	if (no > 0) {
		for (i = 0; no != 0; i++ ) {
			numString[i] = no % 2 + '0';
			no = no / 2;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print8bitBinaryInc0(uint8_t no) {
	char numString[8] = "0";
	int i, index = 0;

	for (i = 0; i<8; i++ ) {
		numString[i] = no % 2 + '0';
		no = no / 2;
	}
	numString[i] = '\0';
	
	index = 7;
	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print8bitBinaryInc0f(uint8_t no) {
	char numString[8] = "0";
	int i, index = 0;

	for (i = 0; i<8; i++ ) {
		numString[i] = no % 2 + '0';
		no = no / 2;
	}
	numString[i] = '\0';
	
	index = 7;
	
	UART_printString("0b ");
	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
		if(i == 4) UART_printString(" ");
	}
}

void UART_print16bitBinaryNumber(uint16_t no) {
	char numString[16] = "0";
	int i, index = 0;

	if (no > 0) {
		for (i = 0; no != 0; i++ ) {
			numString[i] = no % 2 + '0';
			no = no / 2;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print16bitBinaryInc0(uint16_t no) {
	char numString[16] = "0";
	int i, index = 0;

	for (i = 0; i<16; i++ ) {
		numString[i] = no % 2 + '0';
		no = no / 2;
	}
	numString[i] = '\0';
	index = 15;

	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
		
	}
}

void UART_print16bitBinaryInc0f(uint16_t no) {
	char numString[16] = "0";
	int i, index = 0;

	for (i = 0; i<16; i++ ) {
		numString[i] = no % 2 + '0';
		no = no / 2;
	}
	numString[i] = '\0';
	index = 15;

	UART_printString("0b ");
	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
		if((i % 4 ) == 0 && i > 0) UART_printString(" ");
	}
}

void UART_print8bitHexNumber(uint8_t no) {
	char numString[2] = "0";
	int i, index = 0;
	char hexTemp[16] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	if (no > 0) {
		for (i = 0; no != 0; i++ ) {
			char hex = no % 16;
			numString[i] = hexTemp[hex];
			no = no / 16;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print8bitHexInc0(uint8_t no) {
	char hexTemp[16] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	char numString[2];
	
	int i;

	for (i = 0; i<2; i++ ) {
		numString[i] = hexTemp[(no % 16)];
		no = no / 16;
	}
	numString[2] = '\0';
	
	for (i = 1; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print8bitHexInc0f(uint8_t no) {
	char hexTemp[16] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	char numString[2];
	
	int i;

	for (i = 0; i<2; i++ ) {
		numString[i] = hexTemp[(no % 16)];
		no = no / 16;
	}
	numString[2] = '\0';
	
	UART_printString("0x ");
	for (i = 1; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print16bitHexNumber(uint16_t no) {
	char numString[4] = "0";
	int i, index = 0;
	char hexTemp[16] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	if (no > 0) {
		for (i = 0; no != 0; i++ ) {
			numString[i] = hexTemp[(no % 16)];
			no = no / 16;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print16bitHexInc0(uint16_t no) {
	char hexTemp[16] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	char numString[4];
	
	int i;

	for (i = 0; i<4; i++ ) {
		numString[i] = hexTemp[(no % 16)];
		no = no / 16;
	}
	numString[4] = '\0';
	
	for (i = 3; i >= 0; i--) {
		UART_transmit(numString[i]);
	}
}

void UART_print16bitHexInc0f(uint16_t no) {
	char hexTemp[16] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	char numString[4];
	
	int i;

	for (i = 0; i<4; i++ ) {
		numString[i] = hexTemp[(no % 16)];
		no = no / 16;
	}
	numString[4] = '\0';
	
	UART_printString("0x ");
	for (i = 3; i >= 0; i--) {
		UART_transmit(numString[i]);
		if((i % 2 ) == 0 && i > 0) UART_printString(" ");
	}
}