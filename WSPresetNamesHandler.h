/*
 * WSCLOCKHandler.h
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_WSPRESETNAMESHANDLER_H_
#define LIBRARIES_NIXIEMISC_WSPRESETNAMESHANDLER_H_

#include <ConfigItem.h>
#include <WSHandler.h>

class WSPresetNamesHandler: public WSHandler {
public:
	WSPresetNamesHandler(BaseConfigItem& rootConfig) :
			rootConfig(rootConfig) {
	}

	virtual void handle(AsyncWebSocketClient *client, char *data);

private:
	BaseConfigItem& rootConfig;
};

#endif /* LIBRARIES_NIXIEMISC_WSPRESETNAMESHANDLER_H_ */
