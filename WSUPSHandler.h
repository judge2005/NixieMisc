/*
 * WSCLOCKHandler.h
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_WSUPSHANDLER_H_
#define LIBRARIES_NIXIEMISC_WSUPSHANDLER_H_

#include <ConfigItem.h>
#include <WSHandler.h>
#include <UPS.h>
#include <USBRating.h>

class WSUPSHandler: public WSHandler {
public:
	WSUPSHandler(BaseConfigItem& rootConfig, const char *name, UPS &ups, USBRating &usbRating) :
		rootConfig(rootConfig),
			name(name),
			ups(ups),
			usbRating(usbRating) {
	}

	virtual void handle(AsyncWebSocketClient *client, char *data);

private:
	BaseConfigItem& rootConfig;
	const char *name;
	UPS &ups;
	USBRating &usbRating;
};

#endif /* LIBRARIES_NIXIEMISC_WSUPSHANDLER_H_ */
