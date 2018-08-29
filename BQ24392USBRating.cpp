/*
 * BQ24392USBRating.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <BQ24392USBRating.h>

void BQ24392USBRating::reset() {
	chgAl = chgDet = false;
}

String BQ24392USBRating::getString() {
	String usbRating = "100mA";
	if (chgDet) {
		usbRating = ">500mA";
	} else if (chgAl) {
		usbRating = "500mA";
	}

	return usbRating;
}

bool BQ24392USBRating::ratingChanged() {
	bool updateRating = false;

	bool old = chgAl;
	if (digitalRead(chgAlPin) < HIGH) {
		chgAl = true;
	}

	updateRating = old != chgAl;

	old = chgDet;
	if (digitalRead(chgDetPin) > LOW) {
		chgDet = true;
	}

	updateRating = updateRating || old != chgDet;

	return updateRating;
}

void BQ24392USBRating::debug(SafeOLED& oled) {
	if (oled) {
		oled.setCursor(0, 5);
		oled.print("CH:");
		oled.print(chgAl);
		oled.print(",");
		oled.print(digitalRead(chgAlPin));
		oled.setCursor(0, 6);
		oled.print("CD:");
		oled.print(chgDet);
		oled.print(",");
		oled.print(digitalRead(chgDetPin));
	}
}
