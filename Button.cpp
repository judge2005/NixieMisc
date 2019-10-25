/*
 * Button.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <Button.h>

bool Button::state() {
	int buttonValue = getPinValue();	// Goes high when closed

	unsigned long now = millis();

	if (!(now - closedTime > 50)) {
		// Still in blackout period
		return true;
	} else if (buttonValue) {
		closedTime = now;

		return true;
	} else {
		return false;
	}
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

