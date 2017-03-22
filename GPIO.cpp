/*
 * GPIO.cpp
 *
 *  Created on: 22 de mar de 2017
 *      Author: aluno
 */

#include "GPIO.h"
#include <avr/io.h>

GPIO::GPIO(int pin, PortDirection_t dir) {

	if (pin < 7) {
		_pin = &PIND;
		_port = &PORTD;
		_reg_ddr = &DDRD;
	} else {
		pin = pin-8;
		_port = &PORTB;
		_reg_ddr = &DDRB;
		_pin = &PINB;
	}

	// calcular a máscara
		_mask = (1 << pin);

	// configurar DDR
	//setar direção do pino: INPUT(0) ou OUTPUT(1)
	if (dir == INPUT)
		(*_reg_ddr) = (*_reg_ddr) & ~(_mask);
	else
		(*_reg_ddr) = (*_reg_ddr) | _mask;

}

GPIO::~GPIO() {}

void GPIO::set(bool val) {
	// escrever no registrador PORT
	if (val==true)
		(*_port) = (*_port) | _mask;
	else
		(*_port) = (*_port) & ~(_mask);
}

bool GPIO::get() {
	// ler do registrador PIN
	return (*_pin)&_mask;
}
