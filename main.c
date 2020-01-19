#include "MKL05Z4.h"
#include "uart.h"
#include "i2c.h"
#include "acc.h"
#include "cstdio"

extern Queue Q_TX, Q_RX;
extern uint8_t acc_X, acc_Y, acc_Z;
uint8_t X, Y, Z;

int main(void){ 
	i2c_init();
	init_mma();
	init_RXTX_buffers();
	uint8_t hello[] = "1";
	enqueue_string(&Q_TX, hello);
	uartInitialize();
	while(1)
	{
		read_full_xyz();
		enqueue(&Q_TX, acc_X);
		
	}	

}
