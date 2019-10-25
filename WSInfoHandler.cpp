/*
 * WSInfoHandler.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */
#include <WSInfoHandler.h>
#include <ArduinoJson.h>
#include <AsyncWebSocket.h>

void WSInfoHandler::handle(AsyncWebSocketClient *client, char *data) {
	const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(10);
	DynamicJsonBuffer jsonBuffer(bufferSize);

	JsonObject& root = jsonBuffer.createObject();
	root["type"] = "sv.init.clock";

	JsonObject& value = root.createNestedObject("value");
#ifndef ESP32
	value["esp_boot_version"] = ESP.getBootVersion();
#endif
	value["esp_free_heap"] = ESP.getFreeHeap();
	value["esp_sketch_size"] = ESP.getSketchSize();
	value["esp_sketch_space"] = ESP.getFreeSketchSpace();
#ifndef ESP32
	value["esp_flash_size"] = ESP.getFlashChipRealSize();
	value["esp_chip_id"] = String(ESP.getChipId(), HEX);;
#endif
	value["wifi_ip_address"] = WiFi.localIP().toString();
	value["wifi_mac_address"] = WiFi.macAddress();
	value["wifi_ssid"] = WiFi.SSID();
	value["wifi_ap_ssid"] = ssid;

    size_t len = root.measureLength();
    AsyncWebSocketMessageBuffer *buffer = new AsyncWebSocketMessageBuffer(len);
    if (buffer) {
        root.printTo((char *)buffer->get(), len + 1);
        client->text(buffer);
    }
}


