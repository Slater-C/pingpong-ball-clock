#include "Arduino.h"
#include <FastLED.h>
#include "display.h"
#include "clock.h"
#include "text.h"

// Information about the LED strip itself
#define LED_PIN     4
#define NUM_LEDS    133
#define CHIPSET     WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define BRIGHTNESS  50

displayBuffer buffer0;
displayBuffer buffer1;
uint16_t* textbuffer1;
uint8_t hue = 0;
int count1 = 0;
int count2 = 0;
bool invert1 = false;
bool invert2 = false;

void setup(){

    Serial.begin(9600);
    Serial.println("Serial started successfully.");
    
    delay(3000); // power-up safety delay
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
    FastLED.setBrightness( BRIGHTNESS );

    initDisplayBuffer(&buffer0);
    initDisplayBuffer(&buffer1);

    initBufferState(&buffer0, &buffer1);

    writeFormattedTime(getActiveBuffer(), 1234);
    writeFormattedTime(getInactiveBuffer(), 5678);
    backgroundSolidColor(getActiveBuffer(), 100, 255, 100);
    textSolidColor(getActiveBuffer(), 200, 255, 255);
    backgroundSolidColor(getInactiveBuffer(), 100, 255, 100);
    textSolidColor(getInactiveBuffer(), 200, 255, 255);
    textbuffer1 = createTextBuffer(60);

    writeBuffer3x5(textbuffer1, 0, 0, "wowie", 60);
    printTextBuffer(textbuffer1, 60);
}

void loop(){

    
    
    
    //fadeDisplay(10, 20, true, leds);
    //writeFormattedTime(getActiveBuffer(), count);
    
    backgroundSolidColor(getActiveBuffer(), hue, 255, 100);
    textSolidColor(getActiveBuffer(), hue + 100, 0, 255);
    displayTextBuffer(getActiveBuffer(), textbuffer1, count1, 1, 60);
    fadeDisplay(10, 10, true, leds);
    //drawDisplay(getActiveBuffer(), leds);
    FastLED.delay(20);
    //count1--;
    if(count1 < -40){
        count1 = 30;
    }

    hue+= 10;



}


void bounceText(){

    //fadeDisplay(10, 20, true, leds);
    //writeFormattedTime(getActiveBuffer(), count);
    //count++;
    backgroundSolidColor(getActiveBuffer(), hue, 255, 100);
    textSolidColor(getActiveBuffer(), hue + 100, 255, 255);
    displayTextBuffer(getActiveBuffer(), textbuffer1, count1, count2, 60);
    fadeDisplay(10, 10, true, leds);
    //drawDisplay(getActiveBuffer(), leds);
    //FastLED.delay(30);
    
    if(invert1){
        count1--;
    }
    else{
        count1++;
    }
    if(invert2){
        count2--;
    }
    else{
        count2++;
    }
    
    if(count1 >= 8){
        invert1 = true;
    }
    if(count2 >= 2){
        invert2 = true;
    }
    
    if(count1 <= 0){
        invert1 = false;
    }
    if(count2 <= 0){
        invert2 = false;
    }

    hue+= 10;


}

    // FPS testing
    // count++;
    // if(count > 9999){
    //     count = 0;
    // }
    // if(!(count % 10)){
    //     hue++;
    // }
    // if(!(count % 300)){
    //     int duration = millis() - starttime;
    //     int fps = 300 / (duration/1000);
    //     Serial.print("Average FPS over last "); Serial.print(duration/1000); Serial.print(" seconds was "); Serial.print(fps); Serial.println(" FPS.");
    //     starttime = millis();
    // }