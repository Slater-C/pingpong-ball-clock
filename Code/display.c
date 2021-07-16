#include "display.h"
#include "characters.h"
#include <stdio.h>

int getIndex(x, y){
	int index = 0;

	if(y == 0){
		index = x;
		return index;
	}
	else if (y == 2 | y == 4 | y == 6){
		index = 19*y + x;
		return index;
	}
	else{
		index = 19*(y+1) - (x + 1);
		return index;
	}
	
	return 0;
}

displayBuffer* initDisplayBuffer(){

	displayBuffer buffer;
	buffer.layer0->transparent = false;
	buffer.layer1->transparent = true;
	
	for (int i = 0; i < 133; i++){
		buffer.layer0->hue = 0;
		buffer.layer0->sat = 0;
		buffer.layer0->val = 0;

		buffer.layer1->hue = 0;
		buffer.layer1->sat = 0;
		buffer.layer1->val = 0;
	}

	return &buffer;

	// This function creates an empty display buffer and returns a pointer to it.
}

void writeCharacter(displayBuffer* buffer, int character, position pos){

	uint8_t x = 0;
	uint8_t y = pos.y;

	for (int i = 0; i < 15; i++){

		bool state = characters[character][i];
		x = (i % 3) + pos.x;
		
		uint8_t index = getIndex(x, y);
		if (index > 132){
			index = 133;
		}
		
		buffer->layer1[index].transparent = state;
		
		if((i % 3) == 0){
			y++;
		}
	}
}

void textSolidColor(displayBuffer* buffer, uint8_t hue, uint8_t sat, uint8_t val){

	for (int i = 0; i < 133; i++){

		buffer->layer1->hue = hue;
		buffer->layer1->sat = sat;
		buffer->layer1->val = val;
	}
}

void backgroundSolidColor(displayBuffer* buffer, uint8_t hue, uint8_t sat, uint8_t val){

	for (int i = 0; i < 133; i++){

		buffer->layer0->hue = hue;
		buffer->layer0->sat = sat;
		buffer->layer0->val = val;
	}
}

void drawDisplay(displayBuffer* buffer){

	uint8_t h;
    uint8_t s;
    uint8_t v;

	for (int i = 0; i < 133; i++){
		if(!buffer->layer1->transparent){
			
			h = buffer->layer1->hue;
			s = buffer->layer1->sat;
			v = buffer->layer1->val;
		}
		else{
			
			h = buffer->layer0->hue;
			s = buffer->layer0->sat;
			v = buffer->layer0->val;
		}
	}
}