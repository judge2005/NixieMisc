/*
 * WSMenuHandler.h
 *
 *  Created on: Apr 17, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_WSMENUHANDLER_H_
#define LIBRARIES_NIXIEMISC_WSMENUHANDLER_H_

#include <WSHandler.h>
#include <UPS.h>

class WSMenuHandler : public WSHandler {
public:
	WSMenuHandler(UPS& ups) : ups(ups) {}
	virtual void handle(AsyncWebSocketClient *client, char *data);

private:
	UPS& ups;
};


#endif /* LIBRARIES_NIXIEMISC_WSMENUHANDLER_H_ */
