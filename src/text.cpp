#include "text.h"
//#include "Arduino.h"
#include "characters.h"
#include <cstddef>


uint16_t* createTextBuffer(int length){
    uint16_t *textBuffer = new uint16_t[length]();
    return textBuffer;
}

void deleteTextBuffer(uint16_t* textBuffer){
    delete[] textBuffer;
}

void writeBuffer3x5(uint16_t* textbuffer, int x, int y, const char *text, int length){ // length is in pixels! not characters!

    char output = 0;
    uint8_t id = 0;
    int width = 0;

	const char *textlen = text;
	while(*textlen){
		output = *(textlen++);

        id = getID3x5(output);
		uint8_t char_width = font_3x5[id][0];
		width += char_width + 1;
	}

	//create text buffer of size width and return it

	width = 0;

    while(*text){

        output = *(text++);

        id = getID3x5(output);
		//Serial.print("width is"); Serial.println(width);
		uint8_t char_width = font_3x5[id][0];
			for(uint8_t c = 0; c < char_width; c++){
				
				uint8_t column = font_3x5[id][c+1];
				int location = x + c + width;
				if(location > (length - char_width)){
					Serial.println("Text buffer overrun.");
					return;
				}
				textbuffer[location] |= (column << y);
				
			}
			width += char_width + 1;

        //Serial.print("char id is: ASCII | ID |~| "); Serial.print((int)output); Serial.print(" | "); Serial.println(id);
    }
}

void writeBuffer5x7(uint16_t* textbuffer, int x, int y, const char *text, int length){  // length is in pixels! not characters!

    char output = 0;
    uint8_t id = 0;
    int width = 0;

	while(*text){
		output = *(text++);

        id = getID5x7(output);
		uint8_t char_width = font_5x7[id][0];
		width += char_width + 1;
	}

	//create text buffer of size width and return it

	width = 0;

    while(*text){

        output = *(text++);

        id = getID5x7(output);
		uint8_t char_width = font_5x7[id][0];
			for(uint8_t c = 0; c < char_width; c++){
				
				uint8_t column = font_5x7[id][c+1];
				int location = x + c + width;
				if(location > (length - char_width)){
					Serial.println("Text buffer overrun.");
					return;
				}
				textbuffer[location] |= (column << y);
				
			}
			width += char_width + 1;

        //Serial.print("char id is: ASCII | ID |~| "); Serial.print((int)output); Serial.print(" | "); Serial.println(id);
        
        
    }
}

void displayTextBuffer(displayBuffer* buffer, uint16_t* textBuffer, int xOffset, int yOffset, int length){

    for(uint8_t x = 0; x < 19; x++){
        for(uint8_t y = 0; y < 7; y++){
            if(((x - xOffset) >= 0) && ((y - yOffset) >= 0) && ((x - xOffset) < length)){
                buffer->layer1[getIndex(x, y)].transparent = !(0x01 & (textBuffer[x - xOffset] >> (y - yOffset))); 
                // Transform 16 bit columns of the text buffer to the displaybuffer format of a 133 element array
                // with transparency states for each LED.
            }
            else{
                buffer->layer1[getIndex(x, y)].transparent = 1;
            }
        }   
    }
}

void printTextBuffer(uint16_t* textBuffer, int length){
    for(int i = 0; i < length; i++){
        int column = textBuffer[i];
        Serial.print(column); Serial.print(" ");
    }
    Serial.println("");
}