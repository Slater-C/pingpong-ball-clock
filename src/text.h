#pragma once
#include <cstddef>
#include <stdint.h>
#include "display.h"

uint16_t* createTextBuffer(int length);
void deleteTextBuffer(uint16_t* textBuffer);
void writeBuffer3x5(uint16_t* textbuffer, int x, int y, const char* text, int length);
void displayTextBuffer(displayBuffer* buffer, uint16_t* textBuffer, int xOffset, int yOffset, int length);
void printTextBuffer(uint16_t* textBuffer, int length);