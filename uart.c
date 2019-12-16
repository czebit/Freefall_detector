#include "uart.h"

void uartInitialize(void){
	
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; //enable uart0 clock gating
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //enable portb clock gating
	PORTB->PCR[1] |= PORT_PCR_MUX(2); 	//set PTB1 as UART0_TX
	PORTB->PCR[2] |= PORT_PCR_MUX(2);		//set PTB2 as UART0_RX
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);//set clock cource MCGIRCLK for uart 4Mhz in VLPR mode; 1 for 48mhz
	UART0->C2 &= !(UART0_C2_RE_MASK | UART0_C2_TE_MASK); //disable transmitter and receiver
	UART0->C4 |= UART0_C4_OSR(31); 			//osr = 31; oversampling factor = 32
	UART0->BDH |= UART0_BDH_SBR(0);
	UART0->BDL |= UART0_BDL_SBR(78); 		//value 13, for BR=9600 and clk=4mhz; SBR=CLK/(BR*(OSR+1)); value 78 for 19200 and 48mhz
	UART0->BDH &= !UART0_BDH_SBNS_MASK; //set one bit stop
	UART0->C1 &= !(UART0_C1_M_MASK | UART0_C1_PE_MASK); //receiver and transmitter use 8-bit data, no hardware parity generation or checking
	UART0->C2 |= UART0_C2_TE_MASK | UART0_C2_RE_MASK; 	//enable receiver and transmitter
	
}
