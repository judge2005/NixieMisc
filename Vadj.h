/*
 * Vadj.h
 *
 *  Created on: Mar 11, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_VADJ_H_
#define LIBRARIES_NIXIEMISC_VADJ_H_

#include <Arduino.h>

class Vadj {
public:
	Vadj(uint8_t pin, uint8_t maxDuty) : pin(pin), maxDuty(maxDuty) {
	}

	virtual void setVoltage(uint8_t vout) = 0;

protected:
	int getDuty(uint8_t vout) {
		static const float vcc = 3.3;
		static const float radj = 0.0;

		float vadj = 1.26+(radj+30.0)*((1.26/10.2)-((vout-1.26)/1208.0));
		int duty = roundf((vadj*maxDuty)/vcc);

		return constrain(duty, 0, maxDuty);
	}

protected:
	uint8_t pin;

private:
	uint8_t maxDuty;
};

#endif /* LIBRARIES_NIXIEMISC_VADJ_H_ */
