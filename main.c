#include "MKL05Z4.h"
#include "uart.h"
#include "i2c.h"
#include "acc.h"
#include "TPM.h"

extern Queue Q_TX, Q_RX;

int main(void){ 
	tpmInitialize();
	uartInitialize();
	i2c_init();
	init_mma();
	while(1)
	{
	}	
}
