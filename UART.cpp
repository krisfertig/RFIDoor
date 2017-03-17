/*
 * UART.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#include "UART.h"
#include <avr/io.h>

UART::UART(int br, int db, int pr, int sb)
//inicialização padrão dos parâmetros/atributos
: _baudrate(br),
  _databits(db),
  _parity(pr),
  _stopbits(sb)
{
	UBRR0 = F_CPU / (16ul *_baudrate) - 1;

	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (3<<UCSZ00);
}

UART::~UART() {
	// TODO Auto-generated destructor stub
}

void UART::put(unsigned char data) {

	/* Wait for empty transmit buffer */
	// wait until UDR is empty
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char UART::get()
{
	// wait until data is received
	while ( !(UCSR0A & (1<<RXC0)) );

	// return received data
	return UDR0;
}
