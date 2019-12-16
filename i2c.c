#include "i2c.h"

#define SCL_PIN 3
#define SDA_PIN 4
void i2cInit(void){

	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK; //enable clock gating for I2C
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //enlable clock gating for PORTB
	PORTB->PCR[SCL_PIN] |= PORT_PCR_MUX(2); // using PTB3 as i2c_scl
	PORTB->PCR[SDA_PIN] |= PORT_PCR_MUX(2); // using PTB4 as i2c_sda
	
}
