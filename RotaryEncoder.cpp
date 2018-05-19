/*
 * RotaryEncodr.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <RotaryEncoder.h>

int RotaryEncoder::getRotation() {
	// read the current state of the current encoder's pins
	getPinValues();

	if ((lastModeA == LOW) && (curModeA == HIGH)) {
		if (curModeB == LOW) {
			curPos--;
		} else {
			curPos++;
		}
	}
	lastModeA = curModeA;
	int rotation = curPos - lastPos;
	lastPos = curPos;

	return rotation;
}
