/*
 * WSClockHandler.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#include <WSPresetValuesHandler.h>

void WSPresetValuesHandler::handle(AsyncWebSocketClient *client, char *data) {
	String json("{\"type\":\"sv.init.presets\", \"value\": {\"");

	StringConfigItem *currentSetItem = (StringConfigItem*)rootConfig.get("current_set");
	String currentSetKey = *currentSetItem;	// set1, set2 etc.

	json.concat("preset\":\"");
	json.concat(currentSetKey);
	json.concat("\"");
	BaseConfigItem *items = rootConfig.get("preset_names");
	if (items != 0) {
		json.concat(",");
		// Without the {}
		json.concat(items->toJSON(true));
		// Change set1_name to set1_label
		json.replace("name", "label");
	}
	json.concat("}}");
	client->text(json);
}


