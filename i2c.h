#ifndef i2c_h
#define i2c_h

#include "MKL05Z4.h"

/*
SCL		PTB3
SDA		PTB4
INT1	NC
INT2	PTA10
*/
#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART	I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN			I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC				I2C0->C1 &= ~I2C_C1_TX_MASK

#define BUSY_ACK 			while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT			while((I2C0->S & I2C_S_IICIF_MASK)==0){}; I2C0->S |= I2C_S_IICIF_MASK;

#define NACK 					I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK		     	  I2C0->C1 &= ~I2C_C1_TXAK_MASK
	
void i2cInit(void);
void write_one_byte(uint8_t data, uint8_t dev, uint8_t address);
uint8_t read_one_byte(uint8_t dev, uint8_t address);
void read_mult_bytes_setup(uint8_t dev, uint8_t address);


#endif
