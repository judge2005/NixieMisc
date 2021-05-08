/*
 * VadjLEDC.h
 *
 *  Created on: Mar 11, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_VADJLEDC_H_
#define LIBRARIES_NIXIEMISC_VADJLEDC_H_

#include <Vadj.h>

#ifdef ESP32
class VadjLEDC: public Vadj {
public:
	VadjLEDC(uint8_t pin) : Vadj(pin, 255) {
		ledcSetup(ledChannel, freq, resolution);
		ledcAttachPin(pin, ledChannel);
	}

	virtual void setVoltage(uint8_t vout) {
		ledcWrite(ledChannel, getDuty(vout));
	}

private:

	static const int freq = 5000;
	static const uint8_t ledChannel = 0;
	static const uint8_t resolution = 8;
};
#endif

#endif /* LIBRARIES_NIXIEMISC_VADJLEDC_H_ */
