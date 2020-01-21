#include "uart.h"

Queue Q_TX;
Queue Q_RX;

void uartInitialize(void){										//uart configuration and initialization
	
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; //enable uart0 clock gating
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //enable portb clock gating
	PORTB->PCR[1] |= PORT_PCR_MUX(2); 	//set PTB1 as UART0_TX
	PORTB->PCR[2] |= PORT_PCR_MUX(2);		//set PTB2 as UART0_RX
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);//1 for 48mhz
	UART0->C2 &= !UART0_C2_RE_MASK;			//disable receiver for configuration
	UART0->C2 &= !UART0_C2_TE_MASK; 		//disable transmitter for configuration
	UART0->C4 |= UART0_C4_OSR(31); 			//osr = 31; oversampling factor = 32
	UART0->BDH |= UART0_BDH_SBR(0);			//set BDH empty
	UART0->BDL |= UART0_BDL_SBR(78); 		//value 13, for BR=9600 and clk=4mhz; SBR=CLK/(BR*(OSR+1)); value 78 for 19200 and 48mhz
	UART0->BDH &= !UART0_BDH_SBNS_MASK; //set one bit stop
	UART0->C1 &= !UART0_C1_M_MASK;			//receiver and transmitter use 8-bit data
	UART0->C1 &= !UART0_C1_PE_MASK; 		//no hardware parity generation or checking
	
	init_RXTX_buffers();
	
	//interrupts configuration:
//	UART0->C2 |= UART0_C2_TIE_MASK; 		//Interrupt when Transmit Data Register is empty
//	UART0->C2 |= UART0_C2_TCIE_MASK; 		//Interrupt when transmission completes
//	UART0->C2 |= UART0_C2_RIE_MASK;	  	//Interrupt when receiver has data ready
	UART0->C2 |= UART0_C2_TE_MASK; 			//enable transmitter
//	UART0->C2 |= UART0_C2_RE_MASK; 			//enable receiver
	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn, 1);
	NVIC_ClearPendingIRQ(UART0_IRQn);
}

void UART0_IRQHandler(void){									//interrupts handler
	NVIC_ClearPendingIRQ(UART0_IRQn);
	if (UART0->S1 & UART0_S1_TDRE_MASK){ //TDRE: Transmit data register empty
		if(!q_empty(&Q_TX)){
			UART0->D = dequeue(&Q_TX);
		}
		else{
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

void send_char(uint8_t c){										//send char to uart using polling
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
	UART0->D = c;
}

void send_string(uint8_t *s){									//send string to uart using polling
	while (*s)
		send_char(*s++);
}

void init_buffer(Queue *q) {									//initialize buffer with default values, zeros
	q->head = 0;
	q->tail = 0;
	q->elements = 0;
}

void init_RXTX_buffers(void){									//initialize Q_TX and Q_RX buffers
	init_buffer(&Q_TX);
	init_buffer(&Q_RX);
}

uint8_t q_empty(Queue *q){										//check for empty buffer, returns 1 for empty
	return q->elements == 0;
}

uint8_t q_full(Queue *q){											//check for full buffer, returns 1 for full
	return q->elements == Q_SIZE;
}

uint8_t enqueue(Queue *q, uint8_t data) {			//enqueue char to buffer, returns 1 for succes, 0 for failure(empty buffer)
	if (!q_full(q)) {
		q->buff[q->head] = data;
		q->elements++;
		q->head++;
		if (q->head >= Q_SIZE) {
			q->head = 0;
		}
		UART0->C2 |= UART0_C2_TIE_MASK;
	}
	if (q->head == q->tail) {
		return 0;
	}
	return 1;
}

uint8_t dequeue(Queue *q) {										//dequeue char from buffer, returns dequeued char
	uint8_t data;
	if (!q_empty(q)) {
		data = q->buff[q->tail];
		q->tail++;
		q->elements--;
		if (q->tail == Q_SIZE) {
			q->tail = 0;
		}
	}
	return data;
}

void enqueue_string(Queue *q, uint8_t *str){	//send string to uart
	while(*str)
		enqueue(q, *str++);
}
