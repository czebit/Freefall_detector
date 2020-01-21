#ifndef acc_h
#define acc_h

#include "MKL05Z4.h"
#include "i2c.h"
#include "extra.h"

#define MMA_ADDRESS 0x1D<<1
#define WHOAMI 0x1A

#define STATUS_REG 0x00
#define OUT_X_MSB_REG 0x01
#define OUT_X_LSB_REG 0x02
#define OUT_Y_MSB_REG 0x03
#define OUT_Y_LSB_REG 0x04
#define OUT_Z_MSB_REG 0x05
#define OUT_Z_LSB_REG 0x06
#define F_SETUP_REG 0x09
#define TRIG_CFG_REG 0x0A
#define SYSMOD_REG 0x0B
#define INT_SOURCE_REG 0x0C
#define WHO_AM_I_REG 0x0D
#define XYZ_DATA_CFG_REG 0x0E
#define HP_FILTER_CUTOFF_REG 0x0F
#define FF_MT_CFG_REG 0x15
#define FF_MT_SRC_REG 0x16
#define FF_MT_THS_REG 0x17
#define FF_MT_COUNT_REG 0x18
#define ASLP_COUNT_REG 0x29
#define CTRL_REG1_REG 0x2A
#define CTRL_REG2_REG 0x2B
#define CTRL_REG3_REG 0x2C
#define CTRL_REG4_REG 0x2D
#define CTRL_REG5_REG 0x2E

uint8_t init_mma(void);
void read_full_xyz(uint8_t *p_X, uint8_t *p_y, uint8_t *p_z);
uint8_t read_x(void);

#endif 
