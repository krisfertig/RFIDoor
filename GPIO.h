/*
 * GPIO.h
 *
 *  Created on: 22 de mar de 2017
 *      Author: aluno
 */

#ifndef GPIO_H_
#define GPIO_H_

class GPIO {
public:

	enum PortDirection_t {
		INPUT = 0,
		OUTPUT = 1
	};

	GPIO(int pin, PortDirection_t dir);
	~GPIO();

	void set(bool val);
	bool get();

private:
	PortDirection_t _dir;
	unsigned char _mask;
	volatile unsigned char * _pin;
	volatile unsigned char * _port;
	volatile unsigned char * _reg_ddr;
};

#endif /* GPIO_H_ */
