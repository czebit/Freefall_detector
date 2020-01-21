#include "TPM.h"

uint8_t n=0;

void tpmInitialize(void){
	
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; 						//clock enable for tmp0
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(0b11);					//clock source choosen MCGIRCLK
	MCG->C1 |= MCG_C1_IRCLKEN_MASK | MCG_C1_IREFS_MASK;
	TPM0->SC |= TPM_SC_CMOD(1) | TPM_SC_PS(5); 		//counting up and prescaler=32
	TPM0->MOD = 1024;											 			//modulo value
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_MSA_MASK;	//software compare mode
	
	TPM0->SC |= TPM_SC_TOIE_MASK; 								//Timer Overflow Interrupt Enable
	
	NVIC_ClearPendingIRQ(TPM0_IRQn);							//clear pending interrupt
	NVIC_EnableIRQ(TPM0_IRQn);										//enable nvic for tpm0 interrupt
	
}

void TPM0_IRQHandler(void){
	
	TPM0->SC |= TPM_SC_TOF_MASK;
	n++;
}
