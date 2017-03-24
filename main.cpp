/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "GPIO.h"
#include "Timer.h"

const int pin_led = 8; //11;
const int pin_bot = 10; //12;

unsigned long tempo = 1000;

UART uart(19200, UART::DATABITS_6, UART::PARITY_EVEN, UART::STOPBITS_2);

GPIO led(pin_led, GPIO::OUTPUT);
GPIO botao(pin_bot, GPIO::INPUT);
Timer timer(1000);

void setup() {}

bool val_botao;
char message[8];

void loop() {

	val_botao = botao.get();
	led.set(botao.get());
	//sprintf(message, "LED: %d\n", val_botao);
	//uart.puts(message);
	//_delay_ms(100);

	sprintf(message, "%d\n", timer.millis());
	uart.puts(message);
}

int main() {
	setup();
	while (true)
		loop();
}
