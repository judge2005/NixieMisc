/*
 * Uptime.cpp
 *
 *  Created on: Nov 27, 2019
 *      Author: mpand
 */

#include <Uptime.h>
#include <Arduino.h>

char *Uptime::uptime() {
	unsigned long now = millis();
	if (lastMillis > now) {
		rollover++;
	}
	lastMillis = now;
	unsigned long long _now = (rollover << 32) + now;
	unsigned long secs = _now / 1000LL, mins = secs / 60;
	unsigned long hours = mins / 60, days = hours / 24;
	secs -= mins * 60;
	mins -= hours * 60;
	hours -= days * 24;
	sprintf(_return, "%d days %02d:%02d:%02d", (byte) days,
			(int) hours, (int) mins, (int) secs);
	return _return;
}
