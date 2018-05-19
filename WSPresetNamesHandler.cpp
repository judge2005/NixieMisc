/*
 * WSClockHandler.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#include <WSPresetNamesHandler.h>

void WSPresetNamesHandler::handle(AsyncWebSocketClient *client, char *data) {
	String json("{\"type\":\"sv.init.preset_names\", \"value\":");
	BaseConfigItem *items = rootConfig.get("preset_names");
	if (items != 0) {
		json.concat(items->toJSON());
	} else {
		json.concat("}");
	}
	json.concat("}");
	client->text(json);
}


