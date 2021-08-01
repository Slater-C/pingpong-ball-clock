#include "Arduino.h"
#include <FastLED.h>
#include "display.h"
#include "clock.h"

// Information about the LED strip itself
#define LED_PIN     15
#define NUM_LEDS    133
#define CHIPSET     WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define BRIGHTNESS  20

displayBuffer buffer0;
displayBuffer buffer1;
uint8_t hue = 0;

void setup(){

    Serial.begin(9600);
    Serial.println("Serial started successfully.");
    
    delay(3000); // power-up safety delay
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
    FastLED.setBrightness( BRIGHTNESS );

    initDisplayBuffer(&buffer0);
    initDisplayBuffer(&buffer1);

    initBufferState(&buffer0, &buffer1);
}

void loop(){

    textSolidColor(getActiveBuffer(), hue+100, 255, 255);
    writeFormattedTime(getActiveBuffer(), 1152);
    //writeCharacter(getActiveBuffer(), 8, 1, 1);
    
    
    backgroundSolidColor(getActiveBuffer(), hue, 255, 255);
    drawDisplay(getActiveBuffer(), leds);
    FastLED.delay(2000);
    flipBuffers();
    writeFormattedTime(getActiveBuffer(), 2222);
    //fadeDisplay(10, 100, leds);
    drawDisplay(getActiveBuffer(), leds);

    FastLED.delay(2000);
    hue+=10;
    //delay(1000);

}
