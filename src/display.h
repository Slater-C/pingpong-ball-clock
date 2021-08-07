#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <FastLED.h>

typedef struct pixel
{
    
    bool transparent;
    uint8_t hue;
    uint8_t sat;
    uint8_t val;

} pixel;

typedef struct displayBuffer
{

    pixel layer0[134];  // Display buffer has an extra space for overflow pixels
    pixel layer1[134];

} displayBuffer;

typedef struct position
{

    uint8_t x;
    uint8_t y;

} position;

typedef struct bufferState
{

    uint8_t bufferNumber;
    displayBuffer* buffers[2];

} bufferState;

int getIndex(int x, int y);
position getPos(int index);
void initDisplayBuffer(displayBuffer* buffer);
void initBufferState(displayBuffer* buffer0, displayBuffer* buffer1);
void flipBuffers();
displayBuffer* getActiveBuffer();
displayBuffer* getInactiveBuffer();
void writeCharacter(displayBuffer* buffer, int character, uint8_t x, uint8_t y);
void textSolidColor(displayBuffer* buffer, uint8_t hue, uint8_t sat, uint8_t val);
void backgroundSolidColor(displayBuffer* buffer, uint8_t hue, uint8_t sat, uint8_t val);
void drawDisplay(displayBuffer* buffer, CRGB leds[]);
void fadeDisplay(uint8_t fadeSteps, int fadeDelay, bool fadeRGB, CRGB leds[]);
void printBufferState(displayBuffer* buffer);
void printCharacter(displayBuffer* buffer, int character);

