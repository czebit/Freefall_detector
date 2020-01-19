#include "acc.h"

int16_t acc_X=0, acc_Y=0, acc_Z=0;

uint8_t init_mma()
{
	  //check for device if it is present
		if(i2c_read_byte(MMA_ADDRESS, WHO_AM_I_REG) == WHOAMI)	{
  		delay_mc(10);
			//set active mode, 14 bit samples and 100 Hz ODR (0x19)
			i2c_write_byte(MMA_ADDRESS, CTRL_REG1_REG, 0b00000111);
			return 1;
		}
		//else error
		return 0;
}

void read_full_xyz()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];
	
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start*/
	
	i2c_read_setup(MMA_ADDRESS, OUT_X_MSB_REG);
	
// Read five bytes in repeated read mode to data array "data[6]"
	for(i = 0; i<3; i++){
		data[i] = i2c_read_mult_bytes(0);
	}
// Read last byte ending repeated read_mode
	data[i] = i2c_read_mult_bytes(1);
	
// save acceleration data into temp variables for all 3-axis into temp[i] array
//data type for temp[i] should be int16_t;
//index number for the data array is multiplied by 2 due to a 14-bit accel. data
	
	for(i=0; i<3; i++){
		temp[i] = (int16_t)((data[2*i]<<8) | data[2*i+1]);
	}
	// Add the following code to align accel. data in the data array for 14 bits
	acc_X = temp[0]/4;
	acc_Y = temp[1]/4;
	acc_Z = temp[2]/4;
}

uint8_t read_X(void){
	uint8_t res;
	res = i2c_read_byte(MMA_ADDRESS, OUT_X_MSB_REG);
	return res;
}
void read_xyz(void)
{
	// sign extend byte to 16 bits - need to cast to signed since function
	// returns uint8_t which is unsigned
	int8_t XH = (int8_t) i2c_read_byte(MMA_ADDRESS, OUT_X_MSB_REG);
	int8_t XL = (int8_t) i2c_read_byte(MMA_ADDRESS, OUT_X_LSB_REG);
	acc_X = (int16_t)((XH<<8) | XL);
	delay_mc(100);
	
	// Add two other 2-axis here
	int8_t YH = (int8_t) i2c_read_byte(MMA_ADDRESS, OUT_Y_MSB_REG);
	int8_t YL = (int8_t) i2c_read_byte(MMA_ADDRESS, OUT_Y_LSB_REG);
	acc_Y = (int16_t)((YH<<8) | YL);
	delay_mc(100);
	
	int8_t ZH = (int8_t) i2c_read_byte(MMA_ADDRESS, OUT_Z_MSB_REG);
	int8_t ZL = (int8_t) i2c_read_byte(MMA_ADDRESS, OUT_Z_LSB_REG);
	acc_Z = (int16_t)((ZH<<8) | ZL);
	delay_mc(100);
	
}



