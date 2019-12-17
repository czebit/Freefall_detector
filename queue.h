#ifndef queue_h
#define queue_h
#include "uart.h"

void init_bufer(Queue *str);
uint16_t add_char(Queue *ptr, uint8_t data);
uint16_t get_char(Queue *ptr, uint8_t *data);

#endif
