/*
 * BlankTimeMonitor.cpp
 *
 *  Created on: May 8, 2020
 *      Author: mpand
 */

#include <BlankTimeMonitor.h>
#include <Arduino.h>

void BlankTimeMonitor::on(bool on) {
	// Keep track of rollover
	unsigned long now = millis();
	if (lastMillis > now) {
		rollover++;
	}
	lastMillis = now;

	if (forceCalc || (on != wasOn)) {
		unsigned long long _now = (rollover << 32) + now;

		if (wasOn) {
			onCount += _now - lastLongMillis;
		} else {
			offCount += _now - lastLongMillis;
		}

		lastLongMillis = _now;
		wasOn = on;
		forceCalc = false;
	}
}

char *BlankTimeMonitor::onTime() {
	forceCalc = true;
	on(wasOn);
	return elapsedTime(onCount, _onReturn);
}

char *BlankTimeMonitor::offTime() {
	forceCalc = true;
	on(wasOn);
	return elapsedTime(offCount, _offReturn);
}

char *BlankTimeMonitor::elapsedTime(long long duration, char *buf) {
	unsigned long secs = duration / 1000LL, mins = secs / 60;
	unsigned long hours = mins / 60, days = hours / 24;
	secs -= mins * 60;
	mins -= hours * 60;
	hours -= days * 24;
	sprintf(buf, "%d days %02d:%02d:%02d", (byte) days,
			(int) hours, (int) mins, (int) secs);
	return buf;
}

