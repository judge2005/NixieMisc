/*
 * WSMenuHandler.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */
#include <WSMenuHandler.h>

String WSMenuHandler::clockMenu = "{\"1\": { \"url\" : \"clock.html\", \"title\" : \"Clock\" }}";
String WSMenuHandler::ledsMenu = "{\"2\": { \"url\" : \"leds.html\", \"title\" : \"LEDs\" }}";
String WSMenuHandler::extraMenu = "{\"3\": { \"url\" : \"extra.html\", \"title\" : \"Extra\" }}";
String WSMenuHandler::presetsMenu = "{\"4\": { \"url\" : \"presets.html\", \"title\" : \"Presets\", \"noNav\" : true }}";
String WSMenuHandler::infoMenu = "{\"5\": { \"url\" : \"info.html\", \"title\" : \"Info\" }}";
String WSMenuHandler::presetNamesMenu = "{\"6\": { \"url\" : \"preset_names.html\", \"title\" : \"Preset Names\", \"noNav\" : true }}";
String WSMenuHandler::upsMenu = "{\"7\": { \"url\" : \"ups.html\", \"title\" : \"UPS\" }}";
String WSMenuHandler::alexaMenu = "{\"7\": { \"url\" : \"alexa.html\", \"title\" : \"Alexa\" }}";
String WSMenuHandler::syncMenu = "{\"8\": { \"url\" : \"sync.html\", \"title\" : \"Sync\" }}";

void WSMenuHandler::handle(AsyncWebSocketClient *client, char *data) {
	String json("{\"type\":\"sv.init.menu\", \"value\":[");
	char *sep = "";
	for (int i=0; items[i] != 0; i++) {
		json.concat(sep);json.concat(*items[i]);sep=",";
	}
	json.concat("]}");
	client->text(json);
}

void WSMenuHandler::setItems(String **items) {
	this->items = items;
}

