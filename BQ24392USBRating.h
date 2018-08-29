/*
 * BQ24392USBRating.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_BQ24392USBRATING_H_
#define LIBRARIES_NIXIEMISC_BQ24392USBRATING_H_

#include "USBRating.h"

class BQ24392USBRating: public USBRating {
public:
	BQ24392USBRating(uint8_t chgAlPin, uint8_t chgDetPin) :
		chgAlPin(chgAlPin), chgDetPin(chgDetPin) {
	}

	virtual bool ratingChanged();
	virtual String getString();
	virtual void reset();
	virtual void debug(SafeOLED& oled);
	virtual bool isHigh() { return chgDet; }

private:
	volatile bool chgAl = false;
	volatile bool chgDet = false;

	uint8_t chgAlPin;
	uint8_t chgDetPin;
};

#endif /* LIBRARIES_NIXIEMISC_BQ24392USBRATING_H_ */
