#include "i2c.h"


void init_i2c(void){

	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK; 							//enable clock gating for I2C
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;					 		//enlable clock gating for PORTB
	
	PORTB->PCR[SCL_PIN] |= PORT_PCR_MUX(2);					//using PTB3 as i2c_scl
	PORTB->PCR[SDA_PIN] |= PORT_PCR_MUX(2);					//using PTB4 as i2c_sda
	
//	I2C0->C2 |= I2C_C2_HDRS_MASK;
	//baud = bus freq/(scl_div+mul)
// 	I2C0->F = (I2C_F_ICR(0x14) | I2C_F_MULT(0));
 	I2C0->F = (I2C_F_ICR(14));
//	I2C0->F = (I2C_F_ICR(0x14) | I2C_F_MULT(1));
	I2C0->C1 |= (I2C_C1_IICEN_MASK );
}

uint8_t i2c_read_byte(uint8_t dev, uint8_t address){
	uint8_t data;
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start*/
	I2C0->D = dev;				/*send devaddress*/
	I2C0->S |= I2C_S_IICIF_MASK;
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

//send device and register addresses
void i2c_read_setup(uint8_t device, uint8_t address){
	I2C_TRAN;
	I2C_M_START;
	I2C0->D = device;
	I2C_WAIT;
	I2C0->D = address;
	I2C_WAIT;
	I2C_M_RSTART;
	I2C0->D =(device|0x1);
	I2C_WAIT;
	I2C_REC;
}

//read a byte and ack/nack as appropriate
uint8_t i2c_read_mult_bytes(uint8_t isLastRead){
	uint8_t data;
	if(isLastRead){       /*If this is the last READ (isLastRead); if no, send NACK; if yes, send ACK*/
			NACK; 				    /*set NACK after read	*/
	}
	else{
			ACK;					    /*ACK after read	*/
	}
	data = I2C0->D;				/*Add a dummy read*/	
	I2C_WAIT;							/*wait for completion*/            			    
	if(isLastRead)	{     //if this is the last READ (isLastRead), if yes, send STOP
			I2C_M_STOP;       /*send stop	*/
	}
	data = I2C0->D; 			/*read data	*/
	return data;					/*return data*/				
}

//using 7bit addressing writes a byte data to dev:address
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data){
	
		I2C_TRAN;							/*set to transmit mode */
		I2C_M_START;					/*send start*/
		I2C0->D = dev;								/*send dev address	*/
		I2C_WAIT;											/*wait for ack */	
		I2C0->D = address;						/*send write address	*/
		I2C_WAIT;											/*wait for ack */		
		I2C0->D = data;								/*send data	*/
		I2C_WAIT;											/*wait for ack*/
		I2C_M_STOP;										/*send Stop*/
	
}
