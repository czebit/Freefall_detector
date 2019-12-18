#include "i2c.h"

#define SCL_PIN 3
#define SDA_PIN 4
#define INT2_PIN 10
void i2cInit(void){

	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK; 							//enable clock gating for I2C
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;					 		//enlable clock gating for PORTB
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;							//Turn on clock to Port A module
	PORTB->PCR[SCL_PIN] |= PORT_PCR_MUX(2);					//using PTB3 as i2c_scl
	PORTB->PCR[SDA_PIN] |= PORT_PCR_MUX(2);					//using PTB4 as i2c_sda
	PORTA->PCR[INT2_PIN] |= PORT_PCR_MUX(1);				//using PTA10 as gpio
	PORTA->PCR[INT2_PIN] |= PORT_PCR_IRQC(0b1010);	//PTA10 is configured for falling edge interrupts
	PORTA->PCR[INT2_PIN] |= PORT_PCR_ISF_MASK; 	    //Clear the interrupt flag
	I2C0->C2 &= !I2C_C2_ADEXT_MASK;									//0 - 7bit address scheme for slave
	I2C0->F  |= I2C_F_MULT(2);											//mul=4
	I2C0->C1 |= I2C_C1_IICEN_MASK; 									//Enables I2C module operation.
	I2C0->C1 |= I2C_C1_IICIE_MASK;									//Enables I2C interrupt requests
	I2C0->C1 |= I2C_C1_TXAK_MASK;										//Transmit Acknowledge Enable
	I2C0->C1 |= I2C_C1_MST_MASK;										//Master Mode Select, 1-master, 0-slave
	I2C0->A1 |= I2C_A1_AD(0x1D);										//default address of accelerator id 0x1D
	
	NVIC_ClearPendingIRQ(I2C0_IRQn);								//Clear NVIC any pending interrupts on I2C
	NVIC_EnableIRQ(I2C0_IRQn);											//Enable NVIC interrupts source for I2C
	NVIC_SetPriority (I2C0_IRQn, 0);
}


void write_one_byte(uint8_t data, uint8_t dev, uint8_t address){
	I2C_TRAN;						/*set to transmit mode */
	I2C_M_START;				/*send start*/
	I2C0->D = dev;  		/*send devaddress */
	I2C_WAIT;						/*wait for ack*/
	I2C0->D = address;	/*send write address */
	I2C_WAIT;
	I2C0->D = data;			/*send data*/
	I2C_WAIT;
	I2C_M_STOP;
}

uint8_t read_one_byte(uint8_t dev, uint8_t address){
	uint8_t data;
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start*/
	I2C0->D = dev;				/*send devaddress*/
	I2C_WAIT;							/*wait for completion */
	I2C0->D = address;		/*send read address */
	I2C_WAIT;							/*wait for completion */
	I2C_M_RSTART;					/*repeated start */
	I2C0->D = (dev|0x1);	/*send devaddress (read) */
	I2C_WAIT;							/*wait for completion */
	I2C_REC;							/*set to recievemode */
	NACK;									/*set NACK after read*/
	data = I2C0->D;				/*dummy read*/
	I2C_WAIT;							/*wait for completion */
	I2C_M_STOP;						/*send stop*/
	data = I2C0->D;				/*read data*/
	return data;
}


