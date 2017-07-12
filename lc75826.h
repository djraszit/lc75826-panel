/*
 * lc75826.h
 *
 *  Created on: 9 lip 2017
 *      Author: root
 */

#ifndef LC75826_H_
#define LC75826_H_

#define GLUE(a, b)     a##b
#define LC7582x_CE		B, 2
#define LC7582x_CLK		B, 5
#define LC7582x_DATA	B, 3
#define LC7582x_CCB		0x41

#define SET_(what, p, m) GLUE(what, p) |= (1 << (m))
#define CLR_(what, p, m) GLUE(what, p) &= ~(1 << (m))
#define GET_(/* PIN, */ p, m) GLUE(PIN, p) & (1 << (m))
#define SET(what, x) SET_(what, x)
#define CLR(what, x) CLR_(what, x)
#define GET(x) (GET_(x))




typedef struct {
	volatile uint8_t CCB_address;

	uint64_t data : 56;

	volatile uint8_t :2; //lsb
	volatile uint8_t ctrl_P0 :1;
	volatile uint8_t ctrl_P1 :1;
	volatile uint8_t ctrl_P2 :1;
	volatile uint8_t ctrl_P3 :1;
	volatile uint8_t ctrl_DR :1; //0 = 1/3-bias drive, 1 = 1/2-bias drive
	volatile uint8_t ctrl_DN :1; //0 = 200 segments, 1 = 208 segments

	volatile uint8_t ctrl_FC0 :1; //lsb
	volatile uint8_t ctrl_FC1 :1;
	volatile uint8_t ctrl_FC2 :1;
	volatile uint8_t ctrl_OC :1; //0 = internal oscilator, 1 = external clock
	volatile uint8_t ctrl_SC :1; //0 = on, 1 = off
	volatile uint8_t ctrl_BU :1; //0 = normal mode, 1 = power saving mode
	volatile uint8_t dir_DD1 :1;
	volatile uint8_t dir_DD0 :1; //msb

} lc75826_struct;



void lc75826_init(lc75826_struct *data, char *text);
void spi_init();
void waitspi(void);
void set_DD(lc75826_struct *data, uint8_t value);
void lc7582x_send_part(lc75826_struct *data);
void lc7582x_send_data(lc75826_struct *data, uint8_t parts);
void set_bit(lc75826_struct *data, uint8_t bit_nr);
void clr_bit(lc75826_struct *data, uint8_t bit_nr);
void putchar_lcd(lc75826_struct *data,uint8_t pos, uint8_t c);
void puttext_lcd(lc75826_struct *data, uint8_t pos, char *text);

#endif /* LC75826_H_ */
