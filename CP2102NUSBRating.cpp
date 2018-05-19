/*
 * CP2102NUSBRating.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <CP2102NUSBRating.h>

void CP2102NUSBRating::reset() {
	chren = chr0 = chr1 = false;
}

String CP2102NUSBRating::getString() {
	String usbRating = "100mA";
	if (chr1) {
		usbRating = ">500mA";
	} else if (chr0) {
		usbRating = "500mA";
	}

	return usbRating;
}

bool CP2102NUSBRating::ratingChanged() {
	bool updateRating = false;

	bool old = chren;
	if (digitalRead(chrenPin) > LOW) {
		chren = true;
	}

	updateRating = old != chren;

	old = chr0;
	if (digitalRead(chr0Pin) > LOW) {
		chr0 = true;
	}

	updateRating = updateRating || old != chr0;

	old = chr1;
	if (digitalRead(chr1Pin) > LOW) {
		chr1 = true;
	}

	updateRating = updateRating || old != chr1;

	return updateRating;
}

void CP2102NUSBRating::debug(SafeOLED& oled) {
	if (oled) {
		oled.setCursor(0, 5);
		oled.print("CH:");
		oled.print(chren);
		oled.print(",");
		oled.print(digitalRead(chrenPin));
		oled.setCursor(0, 6);
		oled.print("C0:");
		oled.print(chr0);
		oled.print(",");
		oled.print(digitalRead(chr0Pin));
		oled.setCursor(0, 7);
		oled.print("C1:");
		oled.print(chr1);
		oled.print(",");
		oled.print(digitalRead(chr1Pin));
	}
}
