#include "acc.h"

void acc_init (void)
{
     unsigned char reg_val = 0;
     write_one_byte(0x40, MMA8451_I2C_ADDRESS, CTRL_REG2_REG);           // Reset all registers to POR values

     do            // Wait for the RST bit to clear
     {
        reg_val = read_one_byte(MMA8451_I2C_ADDRESS, CTRL_REG2_REG) & 0x40;
     }  while (reg_val);

     write_one_byte(0x00, MMA8451_I2C_ADDRESS,XYZ_DATA_CFG_REG);    		// +/-2g range -> 1g = 16384/4 = 4096 counts
     write_one_byte(0x02, MMA8451_I2C_ADDRESS, CTRL_REG2_REG);           // High Resolution mode
     write_one_byte(0x3D, MMA8451_I2C_ADDRESS, CTRL_REG1_REG);          // ODR = 1.56Hz, Reduced noise, Active mode  
}
