#include "pwrmode.h"

void init_VLPR(void){
	SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV1(0);     //bus freq divider
	SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV4(0b100);	//bus freq divider
	SMC->PMPROT |= SMC_PMPROT_AVLP_MASK; 				//Allow Very-Low-Power Modes, VLPR, VLPW and VLPS are allowed
	SMC->PMCTRL |= SMC_PMCTRL_RUNM(0b10); 			//Very-Low-Power Run mode (VLPR)
}

void init_VLPS(void){
	SMC->PMCTRL |= SMC_PMCTRL_STOPM(0b010); //Very-Low-Power Stop mode (VLPS)
}

void exit_VLPR(void){
	SMC->PMCTRL &= !SMC_PMCTRL_RUNM_MASK;
}
