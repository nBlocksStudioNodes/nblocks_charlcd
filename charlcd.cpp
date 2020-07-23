#include "charlcd.h"
#include <string.h>

nBlock_CharLCD::nBlock_CharLCD(uint32_t cols, uint32_t rows, 
					PinName pinRS, PinName pinEN,
					PinName pinD4, PinName pinD5,
					PinName pinD6, PinName pinD7)
					/*
					// Deprecated, not used since the library handles it
					:
					OutD0(pinD0), OutD1(pinD1),
					OutD0(pinD2), OutD1(pinD3),
					OutRS(pinRS), OutEN(PinEN)*/
					{
	// LCD type
	TextLCD::LCDType lcd_type;
	
	// 16x2
	if ((cols == 16) && (rows == 2))
		lcd_type = TextLCD::LCD16x2;

	// 20x4
	else if ((cols == 20) && (rows == 4))
		lcd_type = TextLCD::LCD20x4;

	// Default: 20x4
	else
		lcd_type = TextLCD::LCD20x4;
	
	
	// Instantiate the library
	_lcd = new TextLCD(pinRS, pinEN, pinD4, pinD5, pinD6, pinD7, lcd_type);
	
	// Reset internal buffer and  flag
	for uint32_t i=0; i<257; i++) TextContent[i] = 0;
	data_received = 0;
}

void nBlock_CharLCD::triggerInput(uint32_t inputNumber, uint32_t value) {
	// Copy string to internal buffer
	strcpy(TextContent, (char *)(value) );
	// Set the flag
	data_received = 1;
	
}

void nBlock_CharLCD::endFrame() {
	// If the flag is set, send text to LCD
	if (data_received) {
		data_received = 0;
		_lcd->printf(TextContent);
	}
}