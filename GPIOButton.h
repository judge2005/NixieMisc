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
	GPIOButton(int pin) : pin(pin) {
	    pinMode(pin, INPUT);
	}

protected:
	virtual byte getPinValue();

	int pin;
};

#endif /* LIBRARIES_NIXIEMISC_GPIOBUTTON_H_ */
