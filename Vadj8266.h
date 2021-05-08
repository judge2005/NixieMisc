/*
 * Vadj8266.h
 *
 *  Created on: Mar 11, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_VADJ8266_H_
#define LIBRARIES_NIXIEMISC_VADJ8266_H_

#include <Vadj.h>

#ifdef ESP8266
class Vadj8266: public Vadj {
public:
	Vadj8266(uint8_t pin) : Vadj(pin, range) {
		pinMode(pin, OUTPUT);
		analogWriteFreq(freq);
		analogWriteRange(range);
	}

	virtual void setVoltage(uint8_t vout) {
		analogWrite(pin, getDuty(vout));
	}

private:
	static const uint32_t freq = 4000;
	static const uint8_t range = 100;
};
#endif

#endif /* LIBRARIES_NIXIEMISC_VADJ8266_H_ */
