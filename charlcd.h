#ifndef __CHARLCD
#define __CHARLCD

#include "nworkbench.h"
#include "TextLCD/TextLCD.h"

class nBlock_CharLCD: public nBlockSimpleNode<1> {
public:

    nBlock_CharLCD(uint32_t cols, uint32_t rows,
					PinName pinRS, PinName pinEN,
					PinName pinD4, PinName pinD5,
					PinName pinD6, PinName pinD7);
    void triggerInput(uint32_t inputNumber, uint32_t value);
	void endFrame();
	
   
private:
	// GPIO
	/*
	// Deprecated, not used as the library handles it
	DigitalOut OutD0;
	DigitalOut OutD1;
	DigitalOut OutD2;
	DigitalOut OutD3;
	DigitalOut OutRS;
	DigitalOut OutEN;
	*/
	
	// LCD library instance
	TextLCD * _lcd;
	
	// Buffer to store the string
	char TextContent[257]; // Up to 64x4 + NULL
	
	// Flag indicating text was received
	uint32_t data_received;
	
};





#endif