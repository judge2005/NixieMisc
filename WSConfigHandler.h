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
	WSConfigHandler(BaseConfigItem& rootConfig, const char *name) :
			rootConfig(rootConfig),
			name(name) {
	}

	virtual void handle(AsyncWebSocketClient *client, char *data);

private:
	BaseConfigItem& rootConfig;
	const char *name;
};

#endif /* LIBRARIES_NIXIEMISC_WSCONFIGHANDLER_H_ */
