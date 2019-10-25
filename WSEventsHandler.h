/*
 * WSCLOCKHandler.h
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_WSUPSHANDLER_H_
#define LIBRARIES_NIXIEMISC_WSUPSHANDLER_H_
#ifdef ESP32
#include <ConfigItem.h>
#include <WSHandler.h>

class ListGenerator {
public:
	virtual String getList() = 0;
};

class WSEventsHandler: public WSHandler {
public:
	WSEventsHandler(BaseConfigItem& rootConfig, const char *name, ListGenerator& ticks, ListGenerator& chimes, ListGenerator& strikes, ListGenerator& alarms) :
		rootConfig(rootConfig),
		name(name),
		ticks(ticks),
		chimes(chimes),
		strikes(strikes),
		alarms(alarms)
	{
	}

	virtual void handle(AsyncWebSocketClient *client, char *data);

private:
	BaseConfigItem& rootConfig;
	const char *name;
	ListGenerator &ticks;
	ListGenerator &chimes;
	ListGenerator &strikes;
	ListGenerator &alarms;
};

#endif
#endif /* LIBRARIES_NIXIEMISC_WSUPSHANDLER_H_ */
