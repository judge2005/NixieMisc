/*
 * Uptime.h
 *
 *  Created on: Nov 27, 2019
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_UPTIME_H_
#define LIBRARIES_NIXIEMISC_UPTIME_H_

class Uptime {
public:
	char *uptime();

private:
	unsigned long long rollover = 0;
	unsigned long lastMillis;
	char _return[32];
};

#endif /* LIBRARIES_NIXIEMISC_UPTIME_H_ */
