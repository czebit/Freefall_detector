#include "extra.h"

/*----------------------------------------------------------------------------
	Function making delay of value * 10000 clock cycles
*----------------------------------------------------------------------------*/
void delay_mc(uint32_t value){
	uint32_t delay, x;
	
	for(x=0; x < value; x++){
		for(delay=0; delay < 10000; delay++){};
	}
}
