/*
 * ringbuffer.h
 *
 *  Created on: 4 lip 2017
 *      Author: root
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_



#define BUFFER_SIZE		64


typedef struct {
	volatile uint16_t tail;
	volatile uint16_t head;
	volatile char data[BUFFER_SIZE];
} ringBuffer;


void writeBuf(ringBuffer *rb, char inputData);
char readBuf(ringBuffer *rb);
char is_empty(ringBuffer *rb);
char is_full(ringBuffer *rb);
void copyBuf(ringBuffer *src, ringBuffer *dst);
uint8_t copy_line_from_buffer(ringBuffer *rb, char *str, char bool_data);

#endif /* RINGBUFFER_H_ */
