/*
   UART.c

   Created: 2020-12-08 오후 2:51:06
   Author : PROCESSOR
*/
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

void UART_INIT(void) {
  UCSR0A |= _BV(U2X0);

  UBRR0H = 0x00;
  UBRR0L = 207;

  UCSR0C |= 0x06;

  UCSR0B |= _BV(RXEN0);
  UCSR0B |= _BV(TXEN0);
}

void UART_INIT(unsigned double boud) {
  UCSR0A |= _BV(U2X0); // 비동기 2 배속 모드

  UBRR0H = 0x00;
  
  switch (boud) {
	  case 1200: 	UBRR0L = 1666;	break;
	  case 2400:	UBRR0L = 832;	break;
	  case 4800:	UBRR0L = 416;	break;
	  case 9600: 	UBRR0L = 207;	break;
	  case 14400:	UBRR0L = 138;	break;
	  case 19200:	UBRR0L = 103;	break;
	  case 28800:	UBRR0L = 68;	break;
	  case 38400:	UBRR0L = 51;	break;
	  case 57600:	UBRR0L = 34;	break;
	  case 115200:	UBRR0L = 16;	break;
	  case 230400:	UBRR0L = 8;		break;
	  case 250000:	UBRR0L = 7;		break;
	  case 1000000:	UBRR0L = 1;		break;
	  // case 2000000:	UBRR0L = 0;	break;  // unavailable at 16Mhz
  }
	  
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

void UART_print8bitNumber(uint8_t no) {
  char numString[4] = "0";
  int i, index = 0;

  if (no > 0) {
    for (i = 0; no != 0; i++ ) {
      numString[i] = no % 10 + '\0';
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
      numString[i] = no % 10 + '\0';
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
      numString[i] = no % 10 + '\0';
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
      numString[i] = no % 2 + '\0';
      no = no / 2;
    }
    numString[i] = '\0';
    index = i - 1;
  }

  for (i = index; i >= 0; i--) {
    UART_transmit(numString[i]);
  }
}

void UART_print16bitBinaryNumber(uint8_t no) {
  char numString[16] = "0";
  int i, index = 0;

  if (no > 0) {
    for (i = 0; no != 0; i++ ) {
      numString[i] = no % 2 + '\0';
      no = no / 2;
    }
    numString[i] = '\0';
    index = i - 1;
  }

  for (i = index; i >= 0; i--) {
    UART_transmit(numString[i]);
  }
}

void UART_print8bitHexNumber(uint8_t no) {
  char numString[2] = "0";
  int i, index = 0;
  char hexTemp[16] = {'0', '1', '2', '3', '4', '5', '6',
			'7', '8', '9', 'A', 'B', ',C', 'D', 'E', 'F'};

  if (no > 0) {
    for (i = 0; no != 0; i++ ) {
      numString[i] = hexTemp[(no % 16)] + '\0';
      no = no / 16;
    }
    numString[i] = '\0';
    index = i - 1;
  }

  for (i = index; i >= 0; i--) {
    UART_transmit(numString[i]);
  }
}

void UART_print16bitHexNumber(uint8_t no) {
  char numString[4] = "0";
  int i, index = 0;
  char hexTemp[16] = {'0', '1', '2', '3', '4', '5', '6',
			'7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

  if (no > 0) {
    for (i = 0; no != 0; i++ ) {
      numString[i] = hexTemp[(no % 16)] + '\0';
      no = no / 16;
    }
    numString[i] = '\0';
    index = i - 1;
  }

  for (i = index; i >= 0; i--) {
    UART_transmit(numString[i]);
  }
}