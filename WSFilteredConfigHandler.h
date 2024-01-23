/*
 * WSCLOCKHandler.h
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_WSFILTEREDCONFIGHANDLER_H_
#define LIBRARIES_NIXIEMISC_WSFILTEREDCONFIGHANDLER_H_

#include <ConfigItem.h>
#include <WSHandler.h>

class WSFilteredConfigHandler: public WSHandler {
public:
	typedef String (*CbFunc)();

	WSFilteredConfigHandler(BaseConfigItem& rootConfig, const char *name, const char **excludes) :
		excludes(excludes),
		rootConfig(rootConfig),
		name(name) {
	}

	virtual void handle(AsyncWebSocketClient *client, char *data);

private:
	const char **excludes;

	BaseConfigItem& rootConfig;
	const char *name;
};

#endif /* LIBRARIES_NIXIEMISC_WSFILTEREDCONFIGHANDLER_H_ */
