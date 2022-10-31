/*
 * LDR.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_LDR_H_
#define LIBRARIES_NIXIEMISC_LDR_H_

#include <Arduino.h>

class LDR {
public:
	LDR(const byte adcPin, unsigned long sampleTime) :
		adcPin(adcPin), sampleTime(sampleTime), squared(true), sensorLDRSmoothed((maxLDR - minLDR) / 2) {
	}

	LDR(const byte adcPin, unsigned long sampleTime, bool squared) :
		adcPin(adcPin), sampleTime(sampleTime), squared(squared), sensorLDRSmoothed((maxLDR - minLDR) / 2) {
	}

	byte getNormalizedBrightness(const bool dimming);
	byte getAdjustedBrightness(const bool dimming, const byte scale, const bool on=true);
	byte getAdjustedBrightness(const bool dimming, const byte scale, const byte min, const bool on=true);
	void reset() {
		sensorLDRSmoothed = (maxLDR - minLDR) / 2;
	}

private:
	byte adcPin;
	unsigned long sampleTime;
	bool squared;
	double sensorLDRSmoothed;

	static const double minLDR;
	static const double maxLDR;
};

#endif /* LIBRARIES_NIXIEMISC_LDR_H_ */
