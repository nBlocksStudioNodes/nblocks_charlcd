#ifndef __CHARLCD
#define __CHARLCD

#include "nworkbench.h"
#include "TextLCD/TextLCD.h"


/**
 *  Modified version of TextLCD to remove the automatic line break
 *  when reaching the end of line
 */
class ModifiedTextLCD: public TextLCD {
public:
	ModifiedTextLCD(PinName rs, PinName e, PinName d4, PinName d5, PinName d6, PinName d7, TextLCD::LCDType type = TextLCD::LCD16x2):
	TextLCD(rs, e, d4, d5, d6, d7, type) {}
protected:
	virtual int _putc(int value) {
		if (value == '\n') {
			_column = 0;
			_row++;
			if (_row >= rows()) {
				_row = 0;
			}
		} else {
			// Only write the char to LCD if we did not yet reach
			// the end of current line. Next characters are ignored
			if (_column < columns()) {
				character(_column, _row, value);
				_column++;
			}
			// There is no else, just ignore
		}
		return value;
	}
};


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
	ModifiedTextLCD * _lcd;
	
	// Buffer to store the string
	char TextContent[257]; // Up to 64x4 + NULL
	
	// Flag indicating text was received
	uint32_t data_received;
	
};





#endif