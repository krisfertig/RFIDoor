/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "UART.h"
#include "GPIO.h"

const int pin_led = 11;
const int pin_bot = 12;

unsigned long tempo = 1000;

UART uart(19200, UART::DATABITS_6, UART::PARITY_EVEN, UART::STOPBITS_2);

GPIO led(pin_led, GPIO::OUTPUT);
GPIO botao(pin_bot, GPIO::INPUT);

void setup() {

}

bool ler_botao() {
	return botao.get();
}

void acende_led() {
	return led.set(true);
}

void apaga_led() {
	return led.set(false);
}

void loop() {
	//uart.put(uart.get() + 1);

	//led.set(botao.get());
	if(ler_botao()) {
		acende_led();
	}
	else {
		apaga_led();
	}
}

int main() {
	setup();
	while (true)
		loop();
}
