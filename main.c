#include "MKL05Z4.h"
#include "uart.h"

extern Queue Q_TX;
extern Queue Q_RX;

int main(void){
	init_RXTX_buffers();
	//uint8_t data = 'a';
	uint8_t sznurek[] = "dupa";
	enqueue_string(&Q_TX,sznurek);
	uartInitialize();
	while(1)
	{
//		data=0x41;
//		for(uint16_t i=0; i<10;i++){
//			data++;
//			enqueue(&Q_TX, data);
//		}
	}

}
