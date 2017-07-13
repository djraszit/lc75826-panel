/*
 * lc75826.c
 *
 *  Created on: 9 lip 2017
 *      Author: root
 */
#include <avr/io.h>
#include <ctype.h>
#include <stdlib.h>
#include "lc75826.h"
#include "lc75826_segments.h"


void lc75826_init(lc75826_struct *data, char *text){
	data[0].CCB_address = LC7582x_CCB;
	data[0].ctrl_P0 = 0;
	data[0].ctrl_P1 = 0;
	data[0].ctrl_P2 = 0;
	data[0].ctrl_P3 = 1;
	data[0].ctrl_DR = 1;
	data[0].ctrl_DN = 1;
	data[0].ctrl_FC0 = 0;
	data[0].ctrl_FC1 = 0;
	data[0].ctrl_FC2 = 0;
	data[0].ctrl_OC = 0;
	data[0].ctrl_SC = 0;
	data[0].ctrl_BU = 0;
	puttext_lcd(data, 0, text);
	lc7582x_send_data(data, 4);
}


void set_DD(lc75826_struct *data, uint8_t value) {
	data->dir_DD0 = value & 0x01 ? 1 : 0;
	data->dir_DD1 = value & 0x02 ? 1 : 0;
}

void set_bit(lc75826_struct *data, uint8_t bit_nr) {
	data->data |= (uint64_t) 1ULL << bit_nr;
}

void clr_bit(lc75826_struct *data, uint8_t bit_nr) {
	data->data &= ~(uint64_t) (1ULL << bit_nr);
}

void putchar_lcd(lc75826_struct *data, uint8_t pos, uint8_t c) {
	if (pos > 10) {
		return;
	}
	uint8_t part;
	uint8_t d = 0;
	uint64_t ch = 0;
	if (pos < 3) {
		part = 3;
		d = 5 + ((2 - pos) * 16);
	}
	if (pos >= 3 && pos < 6) {
		part = 2;
		d = 1 + ((5 - pos) * 16);
	}
	if (pos >= 6 && pos < 9) {
		part = 1;
		d = 5 + ((8 - pos) * 16);
	}
	if (pos >= 9 && pos < 11) {
		part = 0;
		d = 21 + ((10 - pos) * 16);
	}
	do {
		if (c >= 48 && c <= 57) {
			ch = digits[c - 48];
			continue;
		}
		if (c >= 65 && c <= 90) {
			ch = chars[c - 65];
			continue;
		}
		if (c >= 97 && c <= 122) {
			ch = chars[c - 97];
			continue;
		}
		if (c == '(') {
			ch = others[0];
			continue;
		}
		if (c == ')') {
			ch = others[1];
			continue;
		}
		if (c == '+') {
			ch = others[2];
			continue;
		}
		if (c == '-') {
			ch = others[3];
			continue;
		}
		if (c == '/') {
			ch = others[4];
			continue;
		}
		if (c == '\\') {
			ch = others[5];
			continue;
		}
		if (c == '#') {
			ch = digits[10];
			continue;
		}
	} while (0);

	data[part].data &= ~((uint64_t)digits[10] << d);

	data[part].data |= (uint64_t) ch << d;

}

void puttext_lcd(lc75826_struct *data, uint8_t pos, char *text) {
	char c;
	while ((c = *text)) {
		putchar_lcd(data, pos, c);
		if (pos++ > 10) {
			break;
		}
		text++;
	}
	lc7582x_send_data(data, 4);
}

void lc7582x_send_part(lc75826_struct *data) {
	uint8_t *dx = (uint8_t*) data;
	CLR(PORT, LC7582x_CE);
	SPDR = *dx++;
	waitspi();
	SET(PORT, LC7582x_CE);
	for (uint8_t i = 0; i < 9; i++) {
		SPDR = *dx++;
		waitspi();
	}
	CLR(PORT, LC7582x_CE);
}

void lc7582x_send_data(lc75826_struct *data, uint8_t parts) {
	for (uint8_t p = 0; p < parts; p++) {
		data[p].CCB_address = LC7582x_CCB;
		set_DD(&data[p], p);
		lc7582x_send_part(&data[p]);
	}
}

