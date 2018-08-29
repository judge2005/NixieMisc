/*
 * WSClockHandler.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#include <WSUPSHandler.h>

void WSUPSHandler::handle(AsyncWebSocketClient *client, char *data) {
	String json("{\"type\":\"sv.init.");
	json.concat(name);
	json.concat("\", \"value\":{");
	StringConfigItem *currentSetItem = (StringConfigItem*)rootConfig.get("current_set");
	String currentSetKey = *currentSetItem;	// set1, set2 etc.
	BaseConfigItem *currentSetName = rootConfig.get((currentSetKey + "_name").c_str());	// The current name of the current set

	char *sep = "";
	if (currentSetName != 0) {
		json.concat(sep);
		json.concat("\"set_icon_");
		json.concat(name);
		json.concat("\":");
		json.concat(currentSetName->toJSON());
		sep=",";
	}
	BaseConfigItem *currentConfig = rootConfig.get(currentSetKey.c_str());
	BaseConfigItem *clockConfig = currentConfig->get(name);
	if (clockConfig != 0) {
		json.concat(sep);
		json.concat(clockConfig->toJSON(true));
	}

	json.concat(", \"power\":\"" + ups.getPowerString() + "\"");
	json.concat(", \"usb_rating\":\"" + usbRating.getString() + "\"");
	json.concat(", \"charge_rate_txt\":\"" + ups.getRateString() + "\"");

	json.concat("}}");
	client->text(json);
}


