/*
 * I2C.c
 *
 * Created: 2020-12-31 오전 12:39:23
 *  Author: justin
 */ 

#include "I2C.h"

void I2C_init(void) {
	DDRC |= (1 << I2C_SCL);
	DDRC |= (1 << I2C_SDA);
	TWBR = 32;
	TWBR = (1 << TWEN) | (1 << TWEA);
}

void I2C_start(void) {
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN) | _BV(TWEA);
	while( !(TWCR & (1 << TWINT)) ); // 시작 완료 대기
}

void I2C_transmit(uint8_t data) {
	TWDR = data;
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	while( !(TWCR & (1 << TWINT)) );
}

uint8_t I2C_receive_ACK(void) {
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	while( !(TWCR & (1 << TWINT)) );
	return TWDR;
}

uint8_t I2C_receive_NACK(void) {
	TWCR = _BV(TWINT) | _BV(TWEN);
	while( !(TWCR & (1 << TWINT)) );
	return TWDR;
}

void I2C_stop(void) {
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN) | _BV(TWEA);
}

