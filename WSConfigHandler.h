/*
 * WSCLOCKHandler.h
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_WSCONFIGHANDLER_H_
#define LIBRARIES_NIXIEMISC_WSCONFIGHANDLER_H_

#include <ConfigItem.h>
#include <WSHandler.h>

class WSConfigHandler: public WSHandler {
public:
	typedef String (*CbFunc)();

	WSConfigHandler(BaseConfigItem& rootConfig, const char *name) :
		cbFunc(NULL),
		rootConfig(rootConfig),
		name(name) {
	}

	WSConfigHandler(BaseConfigItem& rootConfig, const char *name, CbFunc cbFunc) :
		cbFunc(cbFunc),
		rootConfig(rootConfig),
		name(name) {
	}

	virtual void handle(AsyncWebSocketClient *client, char *data);

private:
	CbFunc cbFunc;

	BaseConfigItem& rootConfig;
	const char *name;
};

#endif /* LIBRARIES_NIXIEMISC_WSCONFIGHANDLER_H_ */
