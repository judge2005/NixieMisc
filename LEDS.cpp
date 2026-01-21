/*
 * LEDS.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */
#if defined(ESP8266)

#include <LEDs.h>

void LEDRGB::setLedColorHSV(const byte hue, const byte s, const byte v) {
	// this is the algorithm to convert from RGB to HSV
	unsigned int h = (hue * 192) / 256;  // 0..191
	unsigned int i = h / 32;   // We want a value of 0 thru 5
	unsigned int f = (h % 32) * 8;   // 'fractional' part of 'i' 0..248 in jumps

	unsigned int sInv = 255 - s;  // 0 -> 0xff, 0xff -> 0
	unsigned int fInv = 255 - f;  // 0 -> 0xff, 0xff -> 0
	byte pv = v * sInv / 256;  // pv will be in range 0 - 255
	byte qv = v * (256 - s * f / 256) / 256;
	byte tv = v * (256 - s * fInv / 256) / 256;

	switch (i) {
	case 0:
		r = v;
		g = tv;
		b = pv;
		break;
	case 1:
		r = qv;
		g = v;
		b = pv;
		break;
	case 2:
		r = pv;
		g = v;
		b = tv;
		break;
	case 3:
		r = pv;
		g = qv;
		b = v;
		break;
	case 4:
		r = tv;
		g = pv;
		b = v;
		break;
	case 5:
		r = v;
		g = pv;
		b = qv;
		break;
	}
}

void LEDRGB::ledDisplay(const byte hue, const byte saturation,
		const byte brightness) {
	setLedColorHSV(hue, saturation, brightness);

	for (int n = 0; n < numPixels(); n++) {
//		led_rgb.setLedColorHSV((hue + numPixels() * 256 / numLEDs) % 256, saturation, brightness);
		setPixelColor(n, r, g, b);
	}

	show();
}

void LEDRGB::ledDisplay(const byte pixel) {
	setPixelColor(pixel, r, g, b);
}
#endif
