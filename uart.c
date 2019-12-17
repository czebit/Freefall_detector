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
	//interrupts configuration:
//	UART0->C2 |= UART0_C2_TIE_MASK; 	//Interrupt when Transmit Data Register is empty
	//UART0->C2 |= UART0_C2_TCIE_MASK; 	//Interrupt when transmission completes
//	UART0->C2 |= UART0_C2_RIE_MASK;	  //Interrupt when receiver has data ready
	UART0->C2 |= UART0_C2_TE_MASK | UART0_C2_RE_MASK; 	//enable receiver and transmitter
//	NVIC_SetPriority(UART0_IRQn, 128);
//	NVIC_ClearPendingIRQ(UART0_IRQn);
//	NVIC_EnableIRQ(UART0_IRQn);
	init_bufer(&Q_RX);
	init_bufer(&Q_TX);
}

void UART0_IRQHandler(void){
	uint8_t data;
	NVIC_ClearPendingIRQ(UART0_IRQn);
	if (UART0->S1 & UART0_S1_TDRE_MASK){ //TDRE: Transmit data register empty
		if(!q_empty(&Q_TX)){
			UART0->D = dequeue(&Q_TX, &data);
		}
		else{
		// queue is empty so disable tx
			UART0->C2 &= !UART0_C2_TIE_MASK;
		}
	}
	
	if (UART0->S1 & UART0_S1_RDRF_MASK){ //RDRF: Receiver data register full
			if (!q_full(&Q_RX)){
				enqueue(&Q_RX, UART0->D);
				}
			else{
				// error -queue full.
			}
	}
}

void send_char(uint16_t c){
	
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
	UART0->D = c;
}

void send_string(uint8_t *s){
	
	while (*s)
		send_char(*s++);
}

void init_bufer(Queue *q) {
	q->head = 0;
	q->tail = 0;
	q->elements = 0;
}

uint8_t q_empty(Queue *q){
	return q->elements == 0;
}

uint8_t q_full(Queue *q){
	return q->elements == Q_SIZE;
}

uint8_t enqueue(Queue *q, uint8_t data) {
	if (q_full(q)) {
		return 0;
	}
	q->buff[q->head] = data;
	q->elements++;
	q->head++;
	if (q->head >= Q_SIZE) {
		q->head = 0;
	}
	if (q->head == q->tail) {
		return 0;
	}
	return data;
}

uint8_t dequeue(Queue *q, uint8_t *data) {
	if (q_empty(q)) {
		return 0;
	}
	*data = q->buff[q->tail];
	q->tail++;
	q->elements--;
	if (q->tail == Q_SIZE) {
		q->tail = 0;
	}
	return *data;
}
