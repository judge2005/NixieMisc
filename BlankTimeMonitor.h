/*
 * BlankTimeMonitor.h
 *
 *  Created on: May 8, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_BLANKTIMEMONITOR_H_
#define LIBRARIES_NIXIEMISC_BLANKTIMEMONITOR_H_

class BlankTimeMonitor {
public:
	void on(bool on);
	char *onTime();
	char *offTime();

private:
	char *elapsedTime(long long duration, char* buf);

	bool wasOn = false;
	bool forceCalc = true;
	unsigned long long onCount = 0;
	unsigned long long offCount = 0;
	unsigned long long lastLongMillis = 0;
	unsigned long long rollover = 0;
	unsigned long lastMillis;
	char _onReturn[32];
	char _offReturn[32];
};

#endif /* LIBRARIES_NIXIEMISC_BLANKTIMEMONITOR_H_ */
