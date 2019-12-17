#ifndef uart_h
#define uart_h
#define Q_SIZE 32
#include "MKL05Z4.h" 

typedef struct {
	uint8_t head;
	uint8_t tail;
	uint8_t buff[Q_SIZE];
	uint8_t elements;
}Queue;

static Queue Q_TX;
static Queue Q_RX;
uint8_t q_empty(Queue *q);
uint8_t q_full(Queue *q);
void uartInitialize(void);
void send_string(uint8_t s[]);
void send_char(uint16_t c);
void init_bufer(Queue *q);
uint8_t enqueue(Queue *q, uint8_t data);
uint8_t dequeue(Queue *q, uint8_t *data);

#endif

//int add_string_cyc_buff();
//Queue CYC_BUFF;
