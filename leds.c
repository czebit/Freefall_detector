#include "leds.h"												//Declarations

const uint32_t red_mask = 1UL<<8;				//PTB8
const uint32_t green_mask = 1UL<<9;			//PTB9 
const uint32_t blue_mask = 1UL<<10;			//PTB10

void ledsInitialize(void){
	
	//Initialize registers	
  SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
  PORTB->PCR[8] = PORT_PCR_MUX(1);
  PORTB->PCR[9] = PORT_PCR_MUX(1);
  PORTB->PCR[10] = PORT_PCR_MUX(1);
	
	FPTB->PSOR = red_mask;          /* switch Red LED off */
	FPTB->PSOR = green_mask;        /* switch Green LED off */
	FPTB->PSOR = blue_mask;					/* switch Blue LED off */
	
	FPTB->PDDR |= red_mask;
	FPTB->PDDR |= green_mask;
	FPTB->PDDR |= blue_mask;
}

void ledRedOn (void) {
	FPTB->PCOR=red_mask;
	FPTB->PSOR=green_mask;
	FPTB->PSOR=blue_mask;
}

void ledGreenOn (void) {
	FPTB->PCOR=green_mask;
	FPTB->PSOR=red_mask;
	FPTB->PSOR=blue_mask;
}

void ledsOff (void) {
		FPTB->PSOR=red_mask;
	  FPTB->PSOR=green_mask;
		FPTB->PSOR=blue_mask;
}

void ledsOn (void) {
		FPTB->PCOR=red_mask;
	  FPTB->PCOR=green_mask;
		FPTB->PCOR=blue_mask;
}
