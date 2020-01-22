#include "MKL05Z4.h"
#include "uart.h"
#include "i2c.h"
#include "acc.h"
#include "TPM.h"
#include "leds.h"
#include "pwrmode.h"
#include "extra.h"

int main(void){ 
	init_tpm();
	init_uart();
	init_i2c();
	init_mma();
	init_mma_interrupts();
	init_leds();
	delay_mc(1000);
	init_VLPR();
	
	while(1)
	{
		
	}	
}
