/*
 * LDR.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <LDR.h>

byte LDR::getNormalizedBrightness(const bool dimming) {
	static const double sensorSmoothCountLDR = 40;
	static const double minLDR = 0;
	static const double maxLDR = 1023;
	static double sensorLDRSmoothed = (maxLDR - minLDR) / 2;
	static unsigned long lastUpdate = 0;

	unsigned long nowMs = millis();

	if (nowMs - lastUpdate > sampleTime) {
		lastUpdate = nowMs;

		int adc = analogRead(adcPin);
		double sensorDiff = adc - sensorLDRSmoothed;
		sensorLDRSmoothed += (sensorDiff / sensorSmoothCountLDR);
		sensorLDRSmoothed = constrain(sensorLDRSmoothed, minLDR, maxLDR);
	}

	if (!dimming) {
		return 100;
	}

	return map(sensorLDRSmoothed, minLDR, maxLDR, 5, 100);
}

byte LDR::getAdjustedBrightness(const bool dimming, const byte scale, const bool on) {
	// Scale normalized brightness to range 0..255

	// Always call the normalized brightness routine, to keep track of environment.
	byte brightness = getNormalizedBrightness(dimming);

	if (on) {
		brightness = ((int)brightness) * 255 / 100;

		// Now use a square
		brightness = (long)brightness * (long)brightness / 255L;

		// Scale brightness by ledScale
		brightness = ((int)brightness) * scale / 255;

		brightness = map(brightness, 0, 255, 5, 255);
	} else {
		brightness = 0;
	}

	return brightness;
}


