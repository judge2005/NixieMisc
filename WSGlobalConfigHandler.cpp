/*
 * WSClockHandler.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#include <WSGlobalConfigHandler.h>

void WSGlobalConfigHandler::handle(AsyncWebSocketClient *client, char *data) {
	String json("{\"type\":\"sv.init.");
	json.concat(name);
	json.concat("\", \"value\":{");

	char *sep = "";

	BaseConfigItem *config = rootConfig.get(name);
	if (config != 0) {
		json.concat(sep);
		json.concat(config->toJSON(true));
	}
	json.concat("}}");
	client->text(json);
}


