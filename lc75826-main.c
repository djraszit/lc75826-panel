
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lc75826.h"
#include "ringbuffer.h"

ringBuffer rx_bufer;
volatile char tx_bufer[32];
char bufor[64];
volatile uint8_t new_data = 0;
lc75826_struct lc7582x_data[4];
uint8_t p = 0;

void spi_init() {
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << DORD); // | (1 << CPHA) | (1 << CPOL);
	SPSR |= (1 << SPI2X);
	SPDR;
}

void waitspi(void) {
	while (!(SPSR & (1 << SPIF)))
		;
}

void usart_init(void) {
	DDRD |= (1 << PD1);
	DDRD &= ~(1 << PD0);

#define BAUD 115200
#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
#if USE_2X
	UCSR0A |= (1 << U2X0);
#else
	UCSRA &= ~(1<<U2X);
#endif

	UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // | (1 << TXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

}

void usart_send_byte(uint8_t byte) {
	while (!(UCSR0A & (1 << UDRE0)))
		;
	UDR0 = byte;
}
void usart_send_char(char c) {
	while (!(UCSR0A & (1 << UDRE0)))
		;
	UDR0 = c;
}

void usart_send_string(char *string) {
	char c;
	while ((c = *string++)) {
		usart_send_char(c);
	}
}

ISR(USART_RX_vect) {
	register char data = UDR0;
	if (data == '\n' || data == '\r') {
		new_data = 1;
		data = 0;
	}
	writeBuf(&rx_bufer, data);
	UDR0 = data;
}

int main(void) {
	SET(DDR, LC7582x_CE);
	SET(DDR, LC7582x_CLK);
	SET(DDR, LC7582x_DATA);

	spi_init();
	usart_init();
	usart_send_string("lc75826 test\n\r");

	sei();

	lc75826_init(lc7582x_data, "hello world");

	while (1) {

		if (new_data) {
			new_data = 0;
			usart_send_string("\n\r");
			copy_line_from_buffer(&rx_bufer, bufor, 0);
			if (strncmp(bufor, "set ", 4) == 0) {
				uint8_t bit = atoi(&bufor[4]);
				char *value = strchr(&bufor[5], ' ');
				uint8_t part = atoi(value);

				sprintf((char*) tx_bufer, "bit: %d, part: %d\n\r", bit, part);
				usart_send_string((char*) tx_bufer);

				set_bit(&lc7582x_data[part], bit);

				lc7582x_send_data(lc7582x_data, 4);
				continue;
			}
			if (strncmp(bufor, "clr ", 4) == 0) {
				uint8_t bit = atoi(&bufor[4]);
				char *value = strchr(&bufor[5], ' ');
				uint8_t part = atoi(value);

				sprintf((char*) tx_bufer, "bit: %d, part: %d\n\r", bit, part);
				usart_send_string((char*) tx_bufer);

				clr_bit(&lc7582x_data[part], bit);

				lc7582x_send_data(lc7582x_data, 4);
				continue;
			}

			if (strncmp(bufor, "put ", 4) == 0) {
				sprintf((char*) tx_bufer, "puttext %s\n\r", &bufor[4]);
				usart_send_string((char*) tx_bufer);
				puttext_lcd(lc7582x_data, 0, &bufor[4]);
				continue;
			}

		}

	}

}

