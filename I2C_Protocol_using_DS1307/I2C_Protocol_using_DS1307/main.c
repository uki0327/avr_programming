/*
 * I2C_Protocol_using_DS1307.c
 *
 * Created: 2020-12-31 오전 12:35:12
 * Author : justin
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include "I2C.h"

uint8_t bcd_to_decimal(uint8_t bcd) {
	return (bcd >> 4) * 10 + (bcd & 0x0F); // BCD to Binary
}

uint8_t decimal_to_bcd(uint8_t decimal) {
	return ( ((decimal / 10) << 4) | (decimal % 10) );
}

void write_message(uint8_t no, char *message) { // RTC 데이터 출력
	UART_printString(" ");
	UART_print8bitNumber(no);
	UART_printString(message);
}

int main(void)
{
    uint8_t i;
	I2C_init();	// I2C 초기화
	UART_INIT(9600, 2); // UART 초기화
	UART_printString("* UART is ready...\n");
	
	uint8_t address = 0x68;	// RTC CHIP 의 I2C 주소
	
	// 2014년 9월 1일 월요일 12시 34분 56초
	uint8_t data[] = {56,34,12,2,1,9,14};
	
	// RTC 모듈 시간 설정
	I2C_start();
	I2C_transmit(address << 1);
	// RTC 데이터 기록 메모리 시작 주소 전송
	I2C_transmit(0);
	
	UART_printString("* Setting RTC...\n");
	for(i = 0; i < 7; i++) {
		UART_printString(" ");
		UART_print8bitNumber(i);
		UART_printString("th byte write...\n");
		I2C_transmit(decimal_to_bcd(data[i]));
	}
	
	I2C_stop();
	_delay_ms(2000);
	I2C_start();
	I2C_transmit(address << 1);
	I2C_transmit(0);
	I2C_stop();
	I2C_start();
	I2C_transmit( (address << 1) + 1);
	
	UART_printString("* Time/Date Retrieval...\n");
	
	write_message(bcd_to_decimal(I2C_receive_ACK()), " second\n");
	write_message(bcd_to_decimal(I2C_receive_ACK()), " minute\n");
	write_message(bcd_to_decimal(I2C_receive_ACK()), " hour\n");
	write_message(bcd_to_decimal(I2C_receive_ACK()), " day of week\n");
	write_message(bcd_to_decimal(I2C_receive_ACK()), " day\n");
	write_message(bcd_to_decimal(I2C_receive_ACK()), " month\n");
	write_message(bcd_to_decimal(I2C_receive_NACK()), " year\n");
	
	I2C_stop();
	
    while (1);
}

