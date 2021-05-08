/*
 * GPIOButton.h
 *
 *  Created on: May 10, 2019
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_GPIOBUTTON_H_
#define LIBRARIES_NIXIEMISC_GPIOBUTTON_H_

#include <Button.h>

class GPIOButton: public Button {
public:
	GPIOButton(int pin, bool pulldown) : pin(pin), pulldown(pulldown) {
#ifdef ESP32
		if (pulldown) {
			pinMode(pin, INPUT_PULLDOWN);
		} else {
#endif
			pinMode(pin, INPUT_PULLUP);
#ifdef ESP32
		}
#endif
	}

	GPIOButton(int pin) : pin(pin), pulldown(true) {
	    pinMode(pin, INPUT);
	}

protected:
	virtual byte getPinValue();

	int pin;
	bool pulldown;
};

#endif /* LIBRARIES_NIXIEMISC_GPIOBUTTON_H_ */
