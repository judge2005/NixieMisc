/*
 * RotaryEncoder.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_ROTARYENCODER_H_
#define LIBRARIES_NIXIEMISC_ROTARYENCODER_H_

#include <Arduino.h>

class RotaryEncoder {
public:
	RotaryEncoder() :
		lastModeA(LOW),
		lastModeB(LOW),
		curModeA(LOW),
		curModeB(LOW),
		curPos(0),
		lastPos(0)
	{
	}

	int getRotation();

protected:
	int lastModeA;
	int lastModeB;
	int curModeA;
	int curModeB;
	int curPos;
	int lastPos;

	virtual void getPinValues() = 0;
};

#endif /* LIBRARIES_NIXIEMISC_ROTARYENCODER_H_ */
