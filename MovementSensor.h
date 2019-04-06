/*
 * MovementSensor.h
 *
 *  Created on: Mar 29, 2019
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_MOVEMENTSENSOR_H_
#define LIBRARIES_NIXIEMISC_MOVEMENTSENSOR_H_

#include <Arduino.h>

class MovementSensor {
public:
	MovementSensor(const byte pin) : onTime(0), delayMs(0), pin(pin) {
	}

	void setDelay(byte delayMinutes) {
		delayMs = delayMinutes * 60000;
	}

	void setOnTime(unsigned long onTime) {
		this->onTime = onTime;
	}

	bool isOn() {
		return !isOff();
	}

	bool isOff() {
		int state = digitalRead(pin);

		unsigned long nowMs = millis();

		if (state) {
			onTime = nowMs;	// Sensor will stay high while movement is detected
		}

		return (delayMs != 0) && (nowMs - onTime >= delayMs);	// So zero = always off
	}

private:
	unsigned long onTime;
	unsigned long delayMs;

	const byte pin;
};

#endif /* LIBRARIES_NIXIEMISC_MOVEMENTSENSOR_H_ */
