/*
 * LEDs.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_LEDS_H_
#define LIBRARIES_NIXIEMISC_LEDS_H_

#include <arduino.h>
#include <Adafruit_NeoPixel.h>

struct LEDRGB : public Adafruit_NeoPixel {
	LEDRGB(const byte numLEDs, const byte ledPin) :
		Adafruit_NeoPixel(numLEDs, ledPin, NEO_GRB + NEO_KHZ800) {
	}

	byte r = 0;
	byte g = 255;
	byte b = 255;

	void setLedColorHSV(const byte h, const byte s, const byte v);
	void ledDisplay(const byte hue, const byte saturation, const byte brightness);
	void ledDisplay(const byte pixel);
};

#endif /* LIBRARIES_NIXIEMISC_LEDS_H_ */
