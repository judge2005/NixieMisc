/*
 * SoftMSTimer.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_SOFTMSTIMER_H_
#define LIBRARIES_NIXIEMISC_SOFTMSTIMER_H_

class SoftMSTimer {
public:
	typedef void (*callback_t)(void);

	struct TimerInfo {
		unsigned long interval;
		unsigned long lastCallTick;
		bool enabled;
		callback_t callback;
	};

	SoftMSTimer(TimerInfo **timers) : timers(timers) {

	}

	void loop();

private:
	TimerInfo **timers;
};


#endif /* LIBRARIES_NIXIEMISC_SOFTMSTIMER_H_ */
