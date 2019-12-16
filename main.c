#include "MKL05Z4.h"
#include "uart.h"

int main(void){
	uint8_t data;
	uartInitialize();
	while(1)
	{
		data=0x41;
		for(uint16_t i=0; i<30;i++){
		while(!(UART0->S1 & UART0_S1_TDRE_MASK));
		UART0->D = data;
		data++;
		}
	}

}
