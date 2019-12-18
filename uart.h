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

uint8_t q_empty(Queue *q);
uint8_t q_full(Queue *q);
void uartInitialize(void);
void send_string(uint8_t s[]);
void send_char(uint8_t c);
void init_buffer(Queue *q);
uint8_t enqueue(Queue *q, uint8_t data);
uint8_t dequeue(Queue *q);
void init_RXTX_buffers(void);
void enqueue_string(Queue *q, uint8_t *str);

#endif
