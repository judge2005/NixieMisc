/*
 * WSMenuHandler.h
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_WSMENUHANDLER_H_
#define LIBRARIES_NIXIEMISC_WSMENUHANDLER_H_

#include <Arduino.h>
#include <WString.h>
#include <WSHandler.h>
// #include <UPS.h>

class WSMenuHandler : public WSHandler {
public:
	WSMenuHandler(String **items) : items(items) { }
	virtual void handle(AsyncWebSocketClient *client, char *data);
	void setItems(String **items);

	static String clockMenu;
	static String ledsMenu;
	static String extraMenu;
	static String presetsMenu;
	static String upsMenu;
	static String alexaMenu;
	static String eventsMenu;
	static String mqttMenu;
	static String syncMenu;
	static String infoMenu;
	static String presetNamesMenu;

private:
	String **items;
};


#endif /* LIBRARIES_NIXIEMISC_WSMENUHANDLER_H_ */
