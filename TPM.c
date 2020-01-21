#include "TPM.h"

uint16_t n=0;

void tpmInitialize(void){
	
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; 						//clock enable for tmp0
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3);						//clock source choosen MCGIRC
	MCG->C2 |= MCG_C2_IRCS_MASK;									//Fast internal reference clock selected.
	MCG->SC |= MCG_SC_FCRDIV(0);
	SystemCoreClockUpdate();
	MCG->C1 |= MCG_C1_IRCLKEN_MASK;								//MCGIRCLK active
	TPM0->SC |= TPM_SC_CMOD(0);
	TPM0->SC |=	TPM_SC_PS(0b001); 								//prescaler=4
	TPM0->MOD = 10000;											 				//modulo value
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_MSA_MASK;	//software compare mode
	
	TPM0->SC |= TPM_SC_TOIE_MASK; 								//Timer Overflow Interrupt Enable
	TPM0->SC |= TPM_SC_CMOD(1);
	NVIC_ClearPendingIRQ(TPM0_IRQn);							//clear pending interrupt
	NVIC_EnableIRQ(TPM0_IRQn);										//enable nvic for tpm0 interrupt
}

void TPM0_IRQHandler(void){
	
	TPM0->SC |= TPM_SC_TOF_MASK;
	n++;
}
