/*
 * WSHandler.h
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_WSHANDLER_H_
#define LIBRARIES_NIXIEMISC_WSHANDLER_H_
#include <ESPAsyncWebServer.h>

class WSHandler {
public:
	virtual void handle(AsyncWebSocketClient *client, char *data) = 0;
};


#endif /* LIBRARIES_NIXIEMISC_WSHANDLER_H_ */
