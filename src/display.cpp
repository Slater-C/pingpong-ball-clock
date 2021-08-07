#include "display.h"
#include "characters.h"
#include <cstddef>

bufferState activeBuffer;

int getIndex(int x, int y){
	int index = 0;

	if(y == 0){
		index = x;
	}
	else if ((y == 2) | (y == 4) | (y == 6)){
		index = 19*y + x;
	}
	else{
		index = 19*(y+1) - (x + 1);
	}
	
	if(index > 132){
		index = 133;
	}
	return index;

	// Return the index of an LED for given coordinates.
	// (0, 0) is the top left corner of the display. 
	// LEDs are in switchback rows of 19.
}

position getPos(int index){
	position pos;
	pos.y = index / 19;

	if((pos.y == 0) | (pos.y == 2) | (pos.y == 4) | (pos.y == 6)){
		pos.x = index - (pos.y * 19);
	}
	else{
		pos.x = 19*(pos.y+1) - index - 1;
	}

	return pos;
}

void initDisplayBuffer(displayBuffer* buffer){
	
	for (int i = 0; i < 133; i++){
		buffer->layer0[i].transparent = false;
		buffer->layer1[i].transparent = true;
		
		buffer->layer0[i].hue = 0;
		buffer->layer0[i].sat = 0;
		buffer->layer0[i].val = 0;

		buffer->layer1[i].hue = 0;
		buffer->layer1[i].sat = 0;
		buffer->layer1[i].val = 0;
	}

	// This function sets up an empty display buffer
}

void initBufferState(displayBuffer* buffer0, displayBuffer* buffer1){
	activeBuffer.buffers[0] = buffer0;
	activeBuffer.buffers[1] = buffer1;
	activeBuffer.bufferNumber = 0;
}

void flipBuffers(){
	activeBuffer.bufferNumber = !activeBuffer.bufferNumber;
}

displayBuffer* getActiveBuffer(){
	return activeBuffer.buffers[activeBuffer.bufferNumber];
}

displayBuffer* getInactiveBuffer(){
	return activeBuffer.buffers[!activeBuffer.bufferNumber];
}

void writeCharacter(displayBuffer* buffer, int character, uint8_t x, uint8_t y){

	uint8_t xPos = 0;
	uint8_t yPos = y;

	for (int i = 0; i < 15; i++){

		bool state = numbers[character][i];
		xPos = (i % 3) + x;
		
		uint8_t index = getIndex(xPos, yPos);
		if (index > 132){
			index = 133;
		}
		buffer->layer1[index].transparent = !state;

		if((i % 3) == 2){
			yPos++;
		}
	}
}

void textSolidColor(displayBuffer* buffer, uint8_t hue, uint8_t sat, uint8_t val){

	for (int i = 0; i < 133; i++){

		buffer->layer1[i].hue = hue;
		buffer->layer1[i].sat = sat;
		buffer->layer1[i].val = val;
	}
}

void backgroundSolidColor(displayBuffer* buffer, uint8_t hue, uint8_t sat, uint8_t val){

	for (int i = 0; i < 133; i++){

		buffer->layer0[i].hue = hue;
		buffer->layer0[i].sat = sat;
		buffer->layer0[i].val = val;
	}
}

void drawDisplay(displayBuffer* buffer, CRGB leds[]){

	uint8_t h;
    uint8_t s;
    uint8_t v;

	for (int i = 0; i < 133; i++){
		if(!buffer->layer1[i].transparent){
			
			h = buffer->layer1[i].hue;
			s = buffer->layer1[i].sat;
			v = buffer->layer1[i].val;
		}
		else{
			
			h = buffer->layer0[i].hue;
			s = buffer->layer0[i].sat;
			v = buffer->layer0[i].val;
		}
		leds[i].setHSV(h, s, v);
	}
	FastLED.show();
	flipBuffers();
}

void fadeDisplay(uint8_t fadeSteps, int fadeDelay, bool fadeRGB, CRGB leds[]){

	displayBuffer* next = getActiveBuffer();
	displayBuffer* previous = getInactiveBuffer();
	float step = 0;

	CHSV hsvOut;
	CRGB rgbOut;
	uint8_t h, s, v, h0, s0, v0, h1, s1, v1;

	for(uint8_t fadeIncrement = 1; fadeIncrement < (fadeSteps + 1); fadeIncrement++){
		for (int i = 0; i < 133; i++){
			// Read pixel for active buffer
			if(!next->layer1[i].transparent){
				
				h0 = next->layer1[i].hue;
				s0 = next->layer1[i].sat;
				v0 = next->layer1[i].val;
			}
			else{
				
				h0 = next->layer0[i].hue;
				s0 = next->layer0[i].sat;
				v0 = next->layer0[i].val;
			}

			// Read pixel for previous buffer
			if(!previous->layer1[i].transparent){
				
				h1 = previous->layer1[i].hue;
				s1 = previous->layer1[i].sat;
				v1 = previous->layer1[i].val;
			}
			else{
				
				h1 = previous->layer0[i].hue;
				s1 = previous->layer0[i].sat;
				v1 = previous->layer0[i].val;
			}

			step = (float)fadeIncrement/fadeSteps;

			if(fadeRGB){
				// Use RGB
				CRGB rgb0, rgb1;
				CHSV hsv0(h0, s0, v0); CHSV hsv1(h1, s1, v1);			
				hsv2rgb_rainbow(hsv0, rgb0); hsv2rgb_rainbow(hsv1, rgb1);
				
				rgbOut.r = rgb1.r + ((rgb0.r-rgb1.r) * (step));
				rgbOut.g = rgb1.g + ((rgb0.g-rgb1.g) * (step));
				rgbOut.b = rgb1.b + ((rgb0.b-rgb1.b) * (step));
				leds[i] = rgbOut;
				
			}
			else{
				// Use HSV
				h = h1 + ((h0-h1) * (step));
				s = s1 + ((s0-s1) * (step));
				v = v1 + ((v0-v1) * (step));
				hsvOut.h = h; hsvOut.s = s; hsvOut.v = v;
				leds[i] = hsvOut;
			}
		}
		FastLED.show();
		//Serial.println(" Show fade.");
		FastLED.delay(fadeDelay);
	}
	flipBuffers();
}

void printBufferState(displayBuffer* buffer){
	int x;
	int y;
	for (int i = 0; i < 133; i++){
		x = i % 19;
		y = i / 19;

		if(!buffer->layer1[getIndex(x, y)].transparent){
			Serial.print("\t"); Serial.print(buffer->layer1[getIndex(x, y)].hue);
		}
		else{
			Serial.print("\t"); Serial.print(buffer->layer0[getIndex(x, y)].hue);
		}
		if(x == 18){
			Serial.println("");
		}
	}
}

void printCharacter(displayBuffer* buffer, int character){

	for (int i = 0; i < 15; i++){
		bool state = numbers[character][i];
		Serial.print(state);

		if((i % 3) == 2){
			Serial.println("");
		}
	}
}