/*
UART.c

Created: 2020-12-08 오후 2:51:06
Author : PROCESSOR
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>

#include "UART_malloc.h"

void UART_INIT(unsigned long baud, char x) {
	if (x == 2) UCSR0A |= _BV(U2X0); // 비동기 2배속 모드
	else if (x == 1) UCSR0A = 0x00;
	
	UBRR0H = 0x00;
	
	int UBRRnL_Value;
	if(x == 1) {
		switch(baud) {
			case 2400:		UBRRnL_Value =  416;	break;
			case 4800:		UBRRnL_Value =  207;	break;
			case 9600:		UBRRnL_Value =  103;	break;
			case 14400:		UBRRnL_Value =  68;		break;
			case 19200:		UBRRnL_Value =  51;		break;
			case 28800:		UBRRnL_Value =  34;		break;
			case 38400:		UBRRnL_Value =  25;		break;
			case 57600:		UBRRnL_Value =  16;		break;
			case 76800:		UBRRnL_Value =  12;		break;
			case 115200:	UBRRnL_Value =  8;		break;
			case 230400:	UBRRnL_Value =  3;		break;
			case 250000:	UBRRnL_Value =  3;		break;
			case 500000:	UBRRnL_Value =  1;		break;
			case 1000000:	UBRRnL_Value =  0;		break;
			default:		UBRRnL_Value =  103;	break;
		}
		} else if(x == 2) {
		switch(baud) {
			case 2400:		UBRRnL_Value =  832;	break;
			case 4800:		UBRRnL_Value =  416;	break;
			case 9600:		UBRRnL_Value =  207;	break;
			case 14400:		UBRRnL_Value =  138;	break;
			case 19200:		UBRRnL_Value =  103;	break;
			case 28800:		UBRRnL_Value =  68;		break;
			case 38400:		UBRRnL_Value =  51;		break;
			case 57600:		UBRRnL_Value =  34;		break;
			case 76800:		UBRRnL_Value =  25;		break;
			case 115200:	UBRRnL_Value =  16;		break;
			case 230400:	UBRRnL_Value =  8;		break;
			case 250000:	UBRRnL_Value =  7;		break;
			case 500000:	UBRRnL_Value =  3;		break;
			case 1000000:	UBRRnL_Value =  1;		break;
			default:		UBRRnL_Value =  207;	break;
		}
	}
	
	UBRR0L = UBRRnL_Value;
	
	UCSR0C |= 0x06;

	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);

}

unsigned char UART_receive(void) {
	while ( !(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void UART_transmit(unsigned char data) {
	while ( !(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void UART_printString(char *str) {
	for (int i = 0; str[i]; i++) {
		UART_transmit(str[i]);
	}
}

void UART_printNumber(unsigned long num, char numeral, char zero, char format) {
	
	char san = getStringArrayNum(num, numeral); // String Array Number(자리수)
	UART_printNumber((unsigned long)san, 10, 0, 0);
	UART_printString("  ");
	
	char zeroIndex = 0;
	if (zero == 1) {
		if (numeral == 2) zeroIndex = 4 - (san % 4);
		if (numeral == 8) zeroIndex = 3 - (san % 3);
		if (numeral == 16) zeroIndex = 2 - (san % 2);
		
		san += zeroIndex;
	}
	
	char *numString = (char *)malloc(san); // 배열 동적할당
	int i, index = 0;
	char charTemp[16] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	
	numString[san] = "0";
	
	// 연산부
	if (num > 0) {
		for (i = 0; num != 0; i++ ) {
			if(i<zeroIndex) numString[i] = charTemp[0];
			else numString[i] = charTemp[(num % numeral)];
			
			num = num / numeral;
		}
		numString[i] = '\0';
		index = i - 1;
	}

	// 출력부

	if (format == 1) {
		if (numeral == 2) UART_printString("0b ");
		if (numeral == 8) UART_printString("0 ");
		if (numeral == 16) UART_printString("0x ");
	}
	
	for (i = index; i >= 0; i--) {
		UART_transmit(numString[i]);
		if(format == 1) {
			switch(numeral) {
				case 2:
				if((i % 4 ) == 0 && i > 0 && i < index) UART_printString(" ");
				break;
				case 8:
				if((i % 3 ) == 0 && i > 0 && i < index) UART_printString(" ");
				break;
				case 10:
				if((i % 3 ) == 0 && i > 0 && i < index) UART_printString(",");
				break;
				case 16:
				if((i % 2 ) == 0 && i > 0 && i < index) UART_printString(" ");
				break;
			}
		}
	}
	free(numString);
}

unsigned char getStringArrayNum(unsigned long num, char numeral) {
	char n = 0;

	for(n=0;;n++) {
		if(num < numeral) return n+1;
		num = num / numeral;
	}
	
	return 0;	
}