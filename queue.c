#include "queue.h"

void init_bufer(Queue *str) {
	str->head = 0;
	str->tail = 0;
	str->elements = 0;
}

uint16_t add_char(Queue *ptr, unsigned char data) {
	if(ptr->elements>=Q_SIZE) return 0;
	ptr->buff[ptr->head] = data;
	ptr->elements++;
	ptr->head++;
	if (ptr->head >= Q_SIZE){
		ptr->head = 0;
	}
	if (ptr->head == ptr->tail) return 0;

	return 1;
}

uint16_t get_char(Queue *ptr, unsigned char *data) {
	if (ptr->elements==0) return 0;
	*data = ptr->buff[ptr->tail];
	ptr->tail++;
	ptr->elements--;
	if(ptr->tail==Q_SIZE){
		ptr->tail=0;
	}
	return 1;
}

