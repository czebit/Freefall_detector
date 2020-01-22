#include "pwrmode.h"

void init_VLPR(void){
	SMC->PMPROT |= SMC_PMPROT_AVLP_MASK; //Allow Very-Low-Power Modes, VLPR, VLPW and VLPS are allowed
	SMC->PMCTRL |= SMC_PMCTRL_RUNM(0b10); //Very-Low-Power Run mode (VLPR)
}

void init_VLPS(void){
	SMC->PMCTRL |= SMC_PMCTRL_STOPM(0b010); //Very-Low-Power Stop mode (VLPS)
}