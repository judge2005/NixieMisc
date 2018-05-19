/*
 * MCP23017Button.h
 *
 *  Created on: Apr 18, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_MCP23017BUTTON_H_
#define LIBRARIES_NIXIEMISC_MCP23017BUTTON_H_

#include <SafeMCP23017.h>
#include <Button.h>

class MCP23017Button : public Button {
public:
	MCP23017Button(SafeMCP23017& mcp, byte pin) : mcp(mcp), buttonPin(pin) {
		mcp.pinMode(buttonPin, INPUT);	// Regular switch
		mcp.pullUp(buttonPin, HIGH);	// turn on a 100K pullup internally, so switch closed = low.
	}

protected:
	byte getPinValue() {
		return mcp.digitalRead(buttonPin, 0);
	}

	SafeMCP23017& mcp;
	byte buttonPin;
};

#endif /* LIBRARIES_NIXIEMISC_MCP23017BUTTON_H_ */
