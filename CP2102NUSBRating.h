/*
 * CP2102NUSBRating.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_CP2102NUSBRATING_H_
#define LIBRARIES_NIXIEMISC_CP2102NUSBRATING_H_

#include "USBRating.h"

class CP2102NUSBRating: public USBRating {
public:
	CP2102NUSBRating(uint8_t chrenPin, uint8_t chr0Pin, uint8_t chr1Pin) :
			chrenPin(chrenPin), chr0Pin(chr0Pin), chr1Pin(chr1Pin) {
	}

	virtual bool ratingChanged();
	virtual String getString();
	virtual void reset();
	virtual void debug(SafeOLED& oled);
	virtual bool isHigh() { return chr1; }

private:
	volatile bool chren = false;
	volatile bool chr0 = false;
	volatile bool chr1 = false;

	uint8_t chrenPin;
	uint8_t chr0Pin;
	uint8_t chr1Pin;
};

#endif /* LIBRARIES_NIXIEMISC_CP2102NUSBRATING_H_ */
