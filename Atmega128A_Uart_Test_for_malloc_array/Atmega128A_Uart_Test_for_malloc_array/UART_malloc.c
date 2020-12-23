/*
UART.c

Created: 2020-12-08 오후 2:51:06
Author : PROCESSOR
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <math.h>
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

void UART_printNumber(unsigned char bit, unsigned long num, unsigned char numeral, 
										unsigned char zero, unsigned char format) {
											
	char san = getStringArrayNum(bit, numeral); // String Array Number(자리수)
	char *numString = (char *)malloc(bit / 8); // 배열 동적할당
	int i, index = 0;
	char charTemp[16] = {'0', '1', '2', '3', '4', '5', '6',
	'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	
	numString[san] = "0";

	// 연산부
	if (num > 0) {
		for (i = 0; num != 0; i++ ) {
			numString[i] = charTemp[(num % numeral)];
			num = num / numeral;
		}
		numString[i] = '\0';
		index = i - 1;
		}

	// 출력부
	if (zero == 1) {
		if (numeral == 2) index = san + 4 - (san % 4) - 1;
		if (numeral == 8) index = san + 3 - (san % 3) - 1;
		if (numeral == 16) index = san + 2 - (san % 2) - 1;
	}

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
					if((i % 4 ) == 0 && i > 0) UART_printString(" ");
					break;
				case 8:
					if((i % 3 ) == 0 && i > 0) UART_printString(" ");
					break;
				case 10:
					if((i % 3 ) == 0 && i > 0) UART_printString(",");
					break;
				case 16:
					if((i % 2 ) == 0 && i > 0) UART_printString(" ");
					break;
			}
		}
	}
	free(numString);
}

unsigned char getStringArrayNum(unsigned char bit, unsigned char numeral) {
	unsigned long decMax = 0;
	unsigned long dec;
	unsigned char n = 0;
	int i;
	
	switch(numeral) {
		case 2:
		case 8:
		case 10:
		case 16:
	
			
			for (i = 0; i < bit; i++) {
				decMax = decMax + pow(2,i);
			} // 우선 해당 비트 수에 해당하는 10진수 최대 값을 구한다
			dec = decMax;
			
			for (n=0;; n++) {
				dec -= pow(numeral,n);
				if(dec <= 0) return n;
			} // numeral 진수 자리수를 구한다
		
			
			break;
		default: return 0;	
	}
}