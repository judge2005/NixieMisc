/*
 * LDR.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <LDR.h>

#ifdef ESP32
const double LDR::maxLDR = 4095;
#else
const double LDR::maxLDR = 1023;
#endif

const double LDR::minLDR = 0;

byte LDR::getNormalizedBrightness(const bool dimming) {
	static const double sensorSmoothCountLDR = 40;
	static double adjustedLDR = sensorLDRSmoothed;
	static unsigned long lastUpdate = 0;
	static unsigned long debugTime = 0;

	unsigned long nowMs = millis();

	if (nowMs - lastUpdate > sampleTime) {
		lastUpdate = nowMs;

		int adc = analogRead(adcPin);
//		if ((debugTime++ % 100) == 0) {
//			Serial.print("adc: ");
//			Serial.println(adc);
//		}

		double sensorDiff = adc - sensorLDRSmoothed;
		sensorLDRSmoothed += (sensorDiff / sensorSmoothCountLDR);
		sensorLDRSmoothed = constrain(sensorLDRSmoothed, minLDR, maxLDR);

		if (squared) {
			adjustedLDR = sensorLDRSmoothed * sensorLDRSmoothed / maxLDR;
		} else {
			adjustedLDR = sensorLDRSmoothed;
		}
	}

	if (!dimming) {
		return 100;
	}

	return map(adjustedLDR, minLDR, maxLDR, 5, 100);
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


