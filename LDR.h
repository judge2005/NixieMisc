/*
 * LDR.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_LDR_H_
#define LIBRARIES_NIXIEMISC_LDR_H_

#include <Arduino.h>

struct LDR {
	LDR(const byte adcPin, unsigned long sampleTime) : adcPin(adcPin), sampleTime(sampleTime) {
	}

	byte adcPin;
	unsigned long sampleTime;
	byte getNormalizedBrightness(const bool dimming);
	byte getAdjustedBrightness(const bool dimming, const byte scale, const bool on=true);
};

#endif /* LIBRARIES_NIXIEMISC_LDR_H_ */
