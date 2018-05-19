/*
 * WSMenuHandler.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */
#include <WSMenuHandler.h>

String clockMenu = "{\"1\": { \"url\" : \"clock.html\", \"title\" : \"Clock\" }}";
String ledsMenu = "{\"2\": { \"url\" : \"leds.html\", \"title\" : \"LEDs\" }}";
String extraMenu = "{\"3\": { \"url\" : \"extra.html\", \"title\" : \"Extra\" }}";
String presetsMenu = "{\"4\": { \"url\" : \"presets.html\", \"title\" : \"Presets\" }}";
String upsMenu = "{\"7\": { \"url\" : \"ups.html\", \"title\" : \"UPS\" }}";
String infoMenu = "{\"5\": { \"url\" : \"info.html\", \"title\" : \"Info\" }}";
String presetNamesMenu = "{\"6\": { \"url\" : \"preset_names.html\", \"title\" : \"Preset Names\", \"noNav\" : true}}";

void WSMenuHandler::handle(AsyncWebSocketClient *client, char *data) {
	String json("{\"type\":\"sv.init.menu\", \"value\":[");
	json.concat(clockMenu); json.concat(",");
	json.concat(ledsMenu); json.concat(",");
	json.concat(extraMenu); json.concat(",");
	if (ups) {
		json.concat(upsMenu); json.concat(",");
	}
	json.concat(presetsMenu); json.concat(",");
	json.concat(infoMenu); json.concat(",");
	json.concat(presetNamesMenu);
	json.concat("]}");
	client->text(json);
}


