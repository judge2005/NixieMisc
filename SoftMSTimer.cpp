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
		if (info->lastCallTick == 0 || nowMs - info->lastCallTick >= info->interval) {
			// We triggered, so add interval to lastCallTick. This is better than
			// Setting lastCallTick to nowMs, because we really want to trigger every
			// interval ms, not interval ms from when we last triggered. i.e., if
			// nowMs is 10ms past lastCallTick + interval, we want to set lastCallTick
			// to nowMs-10 so that, on average, we are triggering ever interval ms.
			info->lastCallTick += info->interval;

			// However, we could be so far behind that we would trigger again instantly.
			// We could be SO far behind that we would keep triggering instantly for a
			// long time. This is especially true if this is the first time we have been
			// called and lastCallTick was set to 0!
			//
			// In this case, let's just catch up.
			if (nowMs - info->lastCallTick >= info->interval) {
				info->lastCallTick = nowMs;
			}

			if (info->enabled) {
				info->callback();
			}
		}
	}
}
