#include "MKL05Z4.h"
#include "uart.h"

int main(void){
	uint8_t data;
	uint8_t str[9];
	uartInitialize();
//	while(1)
//	{
		data=0x41;
		for(uint16_t i=0; i<10;i++){
		str[i]=data;
		data++;
		}
		send_string(str);
		send_char('\n');
//	}

}
