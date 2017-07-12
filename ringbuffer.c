/*
 * ringbuffer.c
 *
 *  Created on: 4 lip 2017
 *      Author: root
 */

#include <avr/io.h>
#include "ringbuffer.h"

void writeBuf(ringBuffer *rb, char inputData) {
	rb->data[rb->head] = inputData;
	rb->head++;
	if (rb->head == BUFFER_SIZE) {
		rb->head = 0;
	}
}

char readBuf(ringBuffer *rb) {
	char data = rb->data[rb->tail];
	rb->tail++;
	if (rb->tail == BUFFER_SIZE) {
		rb->tail = 0;
	}
	return data;
}

char is_empty(ringBuffer *rb) {
	return rb->head - rb->tail;
}

char is_full(ringBuffer *rb) {
	if ((rb->head - rb->tail) >= BUFFER_SIZE) {
		return 1;
	} else {
		return 0;
	}
}

void copyBuf(ringBuffer *src, ringBuffer *dst) {
	while ((src->head - src->tail)) {
		writeBuf(dst, readBuf(src));
	}
}

uint8_t copy_line_from_buffer(ringBuffer *rb, char *str, char bool_data) {
	uint8_t count = 0;
	while (rb->head - rb->tail) {
		str[count] = readBuf(rb);
		if (str[count] == '\n' && bool_data == 0) {
			str[count] = 0;
			break;
		}
		count++;
	}
	return count;
}
