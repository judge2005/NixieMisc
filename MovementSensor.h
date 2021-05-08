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
	MovementSensor(const byte pin) : onTime(0), delayMs(0), src(1), pin(pin), callback(0) {
	}

	void setDelay(byte delayMinutes) {
		delayMs = delayMinutes * 60000;
	}

	unsigned long getDelayMs() {
		return delayMs;
	}

	void setSrc(byte src) {
		this->src = src;
	}

	void setOnTime(unsigned long onTime) {
		this->onTime = onTime;
	}

	void setCallback(void (*callback)()) {
		this->callback = callback;
	}

	bool isOn() {
		return !isOff();
	}

	bool isOff() {
		unsigned long nowMs = millis();

		if (src == 1) {	// Local device
			int state = digitalRead(pin);


			if (state) {
				onTime = nowMs;	// Sensor will stay high while movement is detected
				if (callback != 0) {
					(*callback)();
				}
			}
		}

		return (src != 0) && (delayMs != 0) && (nowMs - onTime >= delayMs);	// So zero = always off
	}

	void trigger() {
		onTime = millis();	// Sensor will stay high while movement is detected
	}

private:
	unsigned long onTime;
	unsigned long delayMs;
	byte src;

	const byte pin;
	void (*callback)(void);
};

#endif /* LIBRARIES_NIXIEMISC_MOVEMENTSENSOR_H_ */
