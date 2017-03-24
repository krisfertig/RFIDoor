/*
 * Timer.cpp
 *
 *  Created on: 24 de mar de 2017
 *      Author: aluno
 */

#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long long Timer::_ticks = 0;

Timer::Timer(Hertz freq)
: _frequency(freq)
{
	TCCR0A = 0x00; // Normal operation
	TCCR0B = 0x05; // div 1024
	TIMSK0 = 0x01; // liga interrupção de overflow
	TCNT0 = 0xF0; // 0xFF - 16, que é o que quero contar;
}

Milliseconds Timer::millis() {
	//versão errada
	return _ticks;
}

Microseconds Timer::micros() {

}

void Timer::delay(Milliseconds ms) {

}

void Timer::udelay(Microseconds us) {

}

void Timer::isr_handler() //interrupt service request handler
{
	TCNT0 = 0xF0;
	_ticks++;
}

ISR(TIMER0_OVF_vect) {
	Timer::isr_handler();
}
