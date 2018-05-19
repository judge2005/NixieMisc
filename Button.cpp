/*
 * Button.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <Button.h>

bool Button::state() {
	int buttonValue = getPinValue();

	unsigned long now = millis();

	// Has to stay at that value for 50ms
	if (buttonValue != lastButtonValue) {
		if (now - changeTime > 50)
			lastButtonValue = buttonValue;

		changeTime = now;
	}

	return lastButtonValue;
}

bool Button::clicked() {
	bool nowPressed = state();

	if (!wasPressed && nowPressed) {
		wasPressed = true;
		return true;
	}

	wasPressed = nowPressed;

	return false;
}

