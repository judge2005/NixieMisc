/*
 * LDR.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <LDR.h>

#ifdef ESP32
const double LDR::maxLDR = 4096;
#else
const double LDR::maxLDR = 1024;
#endif

const double LDR::minLDR = 0;

byte LDR::getNormalizedBrightness(const bool dimming, const byte min) {
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

		if (inv) {
			adc = maxLDR - adc;
		}

		double sensorDiff = adc - sensorLDRSmoothed;

		sensorLDRSmoothed += (sensorDiff / sensorSmoothCountLDR);
		sensorLDRSmoothed = constrain(sensorLDRSmoothed, minLDR, maxLDR);

		if (squared) {
			if (inv) {
				adjustedLDR = maxLDR - (maxLDR-sensorLDRSmoothed) * (maxLDR-sensorLDRSmoothed) / maxLDR;
			} else {
				adjustedLDR = sensorLDRSmoothed * sensorLDRSmoothed / maxLDR;
			}
		} else {
			adjustedLDR = sensorLDRSmoothed;
		}
	}

	if (!dimming) {
		return 100;
	}

	return map(adjustedLDR, minLDR, maxLDR, min, 100);
}

void LDR::invert(bool inv) {
	this->inv = inv;
}

byte LDR::getAdjustedBrightness(const bool dimming, const byte scale, const bool on) {
	return getAdjustedBrightness(dimming, scale, 5, on);
}

byte LDR::getAdjustedBrightness(const bool dimming, const byte scale, const byte min, const bool on) {
	// Scale normalized brightness to range 0..255

	// Always call the normalized brightness routine, to keep track of environment.
	byte brightness = getNormalizedBrightness(dimming);

	if (on) {
		brightness = ((int)brightness) * 255 / 100;

		// Now use a square
//		brightness = (long)brightness * (long)brightness / 255L;

		// Scale brightness by ledScale
		brightness = ((int)brightness) * scale / 255;

		brightness = map(brightness, 0, 255, min, 255);
	} else {
		brightness = 0;
	}

	return brightness;
}


