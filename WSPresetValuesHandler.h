/*
 * WSCLOCKHandler.h
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_WSPRESETVALUESHANDLER_H_
#define LIBRARIES_NIXIEMISC_WSPRESETVALUESHANDLER_H_

#include <ConfigItem.h>
#include <WSHandler.h>

class WSPresetValuesHandler: public WSHandler {
public:
	WSPresetValuesHandler(BaseConfigItem& rootConfig) :
			rootConfig(rootConfig) {
	}

	virtual void handle(AsyncWebSocketClient *client, char *data);

private:
	BaseConfigItem& rootConfig;
};

#endif /* LIBRARIES_NIXIEMISC_WSPRESETVALUESHANDLER_H_ */
