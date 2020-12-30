/*
 * I2C.h
 *
 * Created: 2020-12-31 오전 12:39:36
 *  Author: justin
 */ 


#ifndef I2C_H_
#define I2C_H_

#define I2C_SCL PC5
#define I2C_SDA PC4
#include <avr/io.h>

void I2C_init(void);
void I2C_start(void);
void I2C_transmit(uint8_t data);
uint8_t I2C_receive_ACK(void);
uint8_t I2C_receive_NACK(void);
void I2C_stop(void);

#endif /* I2C_H_ */