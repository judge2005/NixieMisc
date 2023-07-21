/*
 * WSInfoHandler.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */
#include <WSInfoHandler.h>
#include <Uptime.h>
#include <ArduinoJson.h>
#include <AsyncWebSocket.h>

void WSInfoHandler::handle(AsyncWebSocketClient *client, char *data) {
	cbFunc();

	static Uptime uptime;
	const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(30);
#ifdef JSON5
	DynamicJsonBuffer jsonBuffer(bufferSize);

	JsonObject& root = jsonBuffer.createObject();
#else
	DynamicJsonDocument doc(bufferSize);
	JsonObject root = doc.to<JsonObject>();
#endif
	root["type"] = "sv.init.clock";

#ifdef JSON5
	JsonObject& value = root.createNestedObject("value");
#else
	JsonVariant value = root.createNestedObject("value");
#endif

#ifndef ESP32
	value["esp_boot_version"] = ESP.getBootVersion();
#endif
	value["esp_free_heap"] = ESP.getFreeHeap();
	value["esp_sketch_size"] = ESP.getSketchSize();
	value["esp_sketch_space"] = ESP.getFreeSketchSpace();
#ifndef ESP32
	value["esp_flash_size"] = ESP.getFlashChipRealSize();
	value["esp_chip_id"] = String(ESP.getChipId(), HEX);
#else
	value["esp_chip_id"] = String(ESP.getChipRevision(), HEX);
#endif
	value["wifi_ip_address"] = WiFi.localIP().toString();
	value["wifi_mac_address"] = WiFi.macAddress();
	value["wifi_ssid"] = WiFi.SSID();
	value["wifi_ap_ssid"] = ssid;
	value["hostname"] = hostname;
	value["software_revision"] = revision;

	value["brightness"] = brightness;
	value["triggered"] = triggered;
	value["clock_on"] = clockOn;

	value["up_time"] = uptime.uptime();
	value["sync_time"] = lastUpdateTime;
	value["sync_failed_msg"] = lastFailedMessage;
	value["sync_failed_cnt"] = failedCount;

	if (pBlankingMonitor) {
		value["on_time"] = pBlankingMonitor->onTime();
		value["off_time"] = pBlankingMonitor->offTime();
	}

#ifdef JSON5
    size_t len = root.measureLength();
#else
    size_t len = measureJson(root);
#endif

    AsyncWebSocketMessageBuffer *buffer = new AsyncWebSocketMessageBuffer(len);
    if (buffer) {
#ifdef JSON5
        root.printTo((char *)buffer->get(), len + 1);
#else
    	serializeJson(root, (char *)buffer->get(), len + 1);
#endif
        client->text(buffer);
    }
}


