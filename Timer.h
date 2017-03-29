/*
 * Timer.h
 *
 *  Created on: 24 de mar de 2017
 *      Author: aluno
 */

#ifndef TIMER_H_
#define TIMER_H_

typedef unsigned long long Hertz;
	typedef unsigned long long Microseconds;
	typedef unsigned long long Milliseconds;

	//F = F_CPU;
	//f_timer = F(16x10⁶)/div;
	//T_min = 1/f_timer;
	//T_max = TOP (2⁸ = 256)/f_timer;

	/* div  | F_min | F_max
	 *  1   |
	 *  8   |
	 *  64  |
	 *  256 |
	 * 1024 |
	 *
	 */

class Timer {
public:

	Timer(Hertz freq);

	Milliseconds millis();
	Microseconds micros();

	void delay(Milliseconds ms);
	void udelay(Microseconds us);

	static void isr_handler(); //interrupt service request handler

private:
	Hertz _frequency;
	static unsigned int _count_timer;
	static unsigned long long _ticks;
	static unsigned long long _us_ticks;
	static unsigned long long _ms_ticks;

};

#endif /* TIMER_H_ */
