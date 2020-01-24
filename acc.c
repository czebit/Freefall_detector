#include "acc.h"
#include "uart.h"
#include "leds.h"
#include "pwrmode.h"

uint8_t acc_X=0, acc_Y=0, acc_Z=0;

int8_t ff = 0;
int8_t h;
int8_t l;
uint8_t val[2];
float s;
uint16_t s2;
extern uint16_t n;

uint8_t init_mma()
{
	  
		if(i2c_read_byte(MMA_ADDRESS, WHO_AM_I_REG) == WHOAMI){ //check for device if it is present
  		delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, CTRL_REG1_REG, 0x00);			//turn on standby mode
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, FF_MT_CFG_REG, 0x38); 		//set freefal detection mode on XYZ axis
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, FF_MT_THS_REG, 0x04); 		//treshold = 0.2g, debouncer increments or clears counter
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, FF_MT_COUNT_REG, 0x5A);		//counter for debounce
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, CTRL_REG4_REG, 0x04);			//freefall interrupt enabled
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, CTRL_REG1_REG, 0x01);			//turn on active mode
			delay_mc(10);
			return 1;
		}
		return 0;
}

void init_mma_interrupts(void){
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;							//Turn on clock to Port A module
	PORTA->PCR[INT2_PIN] |= PORT_PCR_MUX(1);				//using PTA10 as gpio
	PORTA->PCR[INT2_PIN] |= PORT_PCR_IRQC(0b1011);	//PTA10 is configured for both edges interrupts
	PORTA->PCR[INT2_PIN] |= PORT_PCR_ISF_MASK; 	    //Clear the interrupt flag
	
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_SetPriority(PORTA_IRQn, 2);
}

void read_full_xyz(uint8_t *p_x, uint8_t *p_y, uint8_t *p_z)
{
	uint8_t i;
	uint8_t data[6];
	
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start*/
	
	i2c_read_setup(MMA_ADDRESS, OUT_X_MSB_REG);
	
// Read five bytes in repeated read mode to data array "data[6]"
	for(i = 0; i<5; i++){
		data[i] = i2c_read_mult_bytes(0);
	}
// Read last byte ending repeated read_mode
	data[i] = i2c_read_mult_bytes(1);
	
	*p_x = data[0];
	*p_y = data[2];
	*p_z = data[4];
}

void PORTA_IRQHandler(void){
//	exit_VLPR();
	PORTA->PCR[INT2_PIN] |= PORT_PCR_ISF_MASK;
	if (ff == 0){
		TPM0->SC |= TPM_SC_CMOD(1);
		n=0;
		ff = 1;
		ledRedOn();
	}
	else {
		s = (float) n;
		TPM0->SC |= TPM_SC_CMOD(0);
		ff = 0;
		s = (s/100)*(s/100)*490;
		s2 = (uint16_t) s;
		h = (s2>>8);
		l = s2;
		send_char(h);
		send_char(l);
		ledsOff();
//		init_VLPR();
	}
}
