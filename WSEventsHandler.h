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
	WSEventsHandler(BaseConfigItem& rootConfig, const char *name, ListGenerator& listGenerator) :
		rootConfig(rootConfig),
		name(name),
		listGenerator(listGenerator)
	{
	}

	virtual void handle(AsyncWebSocketClient *client, char *data);

private:
	BaseConfigItem& rootConfig;
	const char *name;
	ListGenerator &listGenerator;
};

#endif
#endif /* LIBRARIES_NIXIEMISC_WSUPSHANDLER_H_ */
