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
extern "C" {
#include "esp_ota_ops.h"
#include "esp_image_format.h"
#include "esp_heap_caps.h"
}

static uint32_t sketchSize(sketchSize_t response) {
    esp_image_metadata_t data;
    const esp_partition_t *running = esp_ota_get_running_partition();
    if (!running) return 0;
    const esp_partition_pos_t running_pos  = {
        .offset = running->address,
        .size = running->size,
    };
    data.start_addr = running_pos.offset;
    esp_image_verify(ESP_IMAGE_VERIFY, &running_pos, &data);
    if (response) {
        return running_pos.size - data.image_len;
    } else {
        return data.image_len;
    }
}

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
	value["esp_free_heap"] = ESP.getFreeHeap();
	value["esp_sketch_size"] = ESP.getSketchSize();
	value["esp_sketch_space"] = ESP.getFreeSketchSpace();
#else
	size_t freeHeap = ESP.getFreeHeap();
	size_t free8bitHeap = heap_caps_get_free_size(MALLOC_CAP_8BIT);
	size_t freeIRAMHeap = freeHeap - free8bitHeap;

	value["esp_free_heap"] = free8bitHeap;
	value["esp_sketch_size"] = sketchSize(SKETCH_SIZE_TOTAL);
	value["esp_sketch_space"] = sketchSize(SKETCH_SIZE_FREE);
	value["esp_free_iram_heap"] = freeIRAMHeap;
	value["esp_free_heap_min"] = heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT);
	value["esp_max_alloc_heap"] = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
#endif
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

    String serializedJSON;

#ifdef JSON5
    root.printTo((char *)buffer.get(), len + 1);
#else
    serializeJson(root, serializedJSON);
#endif
    client->text(serializedJSON);
}


