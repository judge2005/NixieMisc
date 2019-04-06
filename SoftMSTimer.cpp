/*
 * SoftMSTimer.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <Arduino.h>
#include <SoftMSTimer.h>

void SoftMSTimer::loop() {
	unsigned long nowMs = millis();
	for (int i = 0; timers[i] != 0; i++) {
		TimerInfo *info = timers[i];
		if (info->enabled
				&& (info->lastCallTick == 0
						|| nowMs - info->lastCallTick >= info->interval)) {
			info->lastCallTick = nowMs;
			info->callback();
		}
	}
}
