#include "acc.h"

uint8_t acc_X=0, acc_Y=0, acc_Z=0;

uint8_t init_mma()
{
	  //check for device if it is present
		if(i2c_read_byte(MMA_ADDRESS, WHO_AM_I_REG) == WHOAMI){
  		delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, CTRL_REG1_REG, 0x20);
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, CTRL_REG3_REG, 0x00);
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, FF_MT_CFG_REG, 0x38);
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, FF_MT_THS_REG, 0x83); //ths = 0.2g, debouncer increments or clears counter
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, FF_MT_COUNT_REG, 0x01);
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, CTRL_REG4_REG, 0x04); //freefall interrupt enabled
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, CTRL_REG5_REG, 0x00);
			delay_mc(10);
			i2c_write_byte(MMA_ADDRESS, CTRL_REG1_REG, 0x21);
			delay_mc(10);
			return 1;
		}
		return 0;
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

	*p_y = data[0];
	*p_z = data[2];
	*p_x = data[4];
}

uint8_t read_x(void){
	uint8_t x = i2c_read_byte(MMA_ADDRESS, OUT_X_MSB_REG);
	return x;
}

