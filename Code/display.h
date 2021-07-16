#pragma once
#include <stdint.h>
#include <stdbool.h>

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

displayBuffer* initDisplayBuffer();
void writeCharacter(displayBuffer* buffer, int character, position pos);
void textSolidColor(displayBuffer* buffer, uint8_t hue, uint8_t sat, uint8_t val);
void backgroundSolidColor(displayBuffer* buffer, uint8_t hue, uint8_t sat, uint8_t val);

