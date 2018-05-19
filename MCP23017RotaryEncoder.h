/*
 * MCP23017RotaryEncoder.h
 *
 *  Created on: Apr 18, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_MCP23017ROTARYENCODER_H_
#define LIBRARIES_NIXIEMISC_MCP23017ROTARYENCODER_H_

#include <RotaryEncoder.h>
#include <SafeMCP23017.h>

class MCP23017RotaryEncoder : public RotaryEncoder {
	MCP23017RotaryEncoder(SafeMCP23017& mcp, byte aPin, byte bPin) :
		mcp(mcp),
		pinA(aPin),
		pinB(bPin)
	{
		mcp.pinMode(aPin, INPUT);	// Rotary encoder A
		mcp.pullUp(aPin, HIGH);		// turn on a 100K pullup internally
		mcp.pinMode(bPin, INPUT);	// Rotary encoder B
		mcp.pullUp(bPin, HIGH);		// turn on a 100K pullup internally
	}

protected:
	void getPinValues() {
		// read the current state of the current encoder's pins
		curModeA = mcp.digitalRead(pinA, 0);
		curModeB = mcp.digitalRead(pinB, 0);
	}

	SafeMCP23017& mcp;
	byte pinA;
	byte pinB;
};

#endif /* LIBRARIES_NIXIEMISC_MCP23017ROTARYENCODER_H_ */
