/*
 * WSInfoHandler.h
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_WSINFOHANDLER_H_
#define LIBRARIES_NIXIEMISC_WSINFOHANDLER_H_

#include <WSHandler.h>

class WSInfoHandler : public WSHandler {
public:
	WSInfoHandler(String& ssid) : ssid(ssid) {}
	virtual void handle(AsyncWebSocketClient *client, char *data);
private:
	String& ssid;
};


#endif /* LIBRARIES_NIXIEMISC_WSINFOHANDLER_H_ */
