/*
 * USBRating.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_USBRATING_H_
#define LIBRARIES_NIXIEMISC_USBRATING_H_
#if defined(ESP8266) && !defined(NO_UPS)

#include <Arduino.h>
#include <SafeOLED.h>

class USBRating {
public:
	virtual bool ratingChanged() = 0;
	virtual String getString() = 0;
	virtual void reset() = 0;
	virtual void debug(SafeOLED& oled) = 0;
	virtual bool isHigh() = 0;
};
#endif
#endif /* LIBRARIES_NIXIEMISC_USBRATING_H_ */
