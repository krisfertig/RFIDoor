/*
 * UART.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#include "UART.h"
#include <avr/io.h>

UART::UART(unsigned long br, DataBits_t db, ParityBits_t pr, StopBits_t sb)
//inicialização padrão dos parâmetros/atributos
: _baudrate(br),
  _databits(db),
  _parity(pr),
  _stopbits(sb)
{
	/* Set frame format: 8N1 (8data, 1stop bit) */
	//UCSR0C = (3<<UCSZ00);

	// set baudrate
	UBRR0 = F_CPU / (16ul *_baudrate) - 1;

	// liga Tx e Rx
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	// set databits
	if (_databits == DATABITS_9) {
		UCSR0C = (UCSR0C & ~(3 << UCSZ00)) | (3 << UCSZ00); // read, modify e update
		UCSR0B = (UCSR0B & ~(1 << UCSZ02)) | (1 << UCSZ02); // read, modify e update
	} else
		UCSR0C = (UCSR0C & ~(3 << UCSZ00)) | (_databits<< UCSZ00);

	// set parity
	UCSR0C = (UCSR0C & ~(3 << UPM00)) | (_parity << UPM00);

	// set stopbits
	UCSR0C = (UCSR0C & ~(1 << USBS0)) | (_stopbits << USBS0);	// read, modify, update

	//unsigned char reg = UCSR0C; // read
	// 1º zera o registrador (aplicando a máscara) e depois coloca o valor de _stopbits
	//reg = (reg & ~(1 << USBS0)) | (_stopbits << USBS0);	// modify
	//UCSR0C = reg; //update

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

void UART::puts(char* str){
	while(*str != '\0'){
		this->put(*str);
		str++;
	}
}
