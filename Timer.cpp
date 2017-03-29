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
unsigned long long Timer::_us_ticks = 0;
unsigned long long Timer::_ms_ticks = 0;
unsigned int Timer::_count_timer = 0;

Timer::Timer(Hertz freq)
: _frequency(freq)
{
	TCCR0A = 0x00; // Normal operation
	TIMSK0 = 0x01; // liga interrupção de overflow

	double f_timer;
	// lógica para selecionar divisor
	if(freq <= 15000) {
		TCCR0B = 0x05; // div 1024
		f_timer = F_CPU/1024;
	} else if (freq <= 62000) {
		TCCR0B = 0x04; // div 256
		f_timer = F_CPU/256;
	} else if (freq <= 250000) {
		TCCR0B = 0x03; // div 64
		f_timer = F_CPU/64;
	} /*else if (freq <= 2000000)
		TCCR0B = 0x02; // div 8
	else if (freq <= 16000000)
		TCCR0B = 0x01; // div 1
	*/

	// calcular ciclos de timer
	int ciclos = f_timer / _frequency;
	_count_timer = ciclos;
	TCNT0 = 0xFF - ciclos;
	//TCNT0 = 0xF0; // 0xFF - 16, que é o que quero contar;
}

Milliseconds Timer::millis() {
	//versão errada
	//return _ticks;
	_ms_ticks = micros() / 1000;
	return _ms_ticks;
}

Microseconds Timer::micros() {
	return _ticks * _us_ticks;
}

void Timer::delay(Milliseconds ms) {
	//chama millis esperando até passar o tempo solicitado
	udelay(ms * 1000);
}

void Timer::udelay(Microseconds us) {
	//chama micros esperando até passar o tempo solicitado

	while(micros() != us);
}

void Timer::isr_handler() //interrupt service request handler
{
	TCNT0 = 0xFF - _count_timer;
	_ticks++;
}

ISR(TIMER0_OVF_vect) {
	Timer::isr_handler();
}
