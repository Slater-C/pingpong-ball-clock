#include "Arduino.h"
#include <FastLED.h>
#include "display.h"
#include "clock.h"
#include "text.h"
#include "effects.h"

// Information about the LED strip itself
#define LED_PIN     4
#define NUM_LEDS    133
#define CHIPSET     WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define BRIGHTNESS  255

displayBuffer buffer0;
displayBuffer buffer1;
uint16_t* textbuffer1;
uint16_t* textbuffer2;
uint16_t* textbuffer3;
uint8_t hue = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;
bool buttonState = false;
bool lastButtonState = false;
int mode = 0;
int lastPress = 0;
bool spawn_snow = false;
bool christmas_alternate = false;

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
    backgroundSolidColor(getActiveBuffer(), 100, 255, 0);
    textSolidColor(getActiveBuffer(), 200, 255, 255);
    backgroundSolidColor(getInactiveBuffer(), 100, 255, 0);
    textSolidColor(getInactiveBuffer(), 200, 255, 255);
    textbuffer1 = createTextBuffer(100);
    textbuffer2 = createTextBuffer(220);
    textbuffer3 = createTextBuffer(90);

    writeBuffer5x7(textbuffer1, 0, 0, "Happy Holidays!", 100);
    writeBuffer5x7(textbuffer2, 0, 0, "Call for a better time:860 706 9223", 220);
    writeBuffer5x7(textbuffer3, 0, 0, "bruh          ", 90);
    //printTextBuffer(textbuffer1, 90);

    pinMode(39, INPUT_PULLDOWN);
}

void loop(){

    
    // buttonState = digitalRead(39);
    // if((buttonState != lastButtonState) && ((lastPress + 400) <= millis())){
    //     //mode++;
    //     Serial.println("button is pressed");
    //     if(mode >= 3){
    //         mode = 0;
    //     }
    //     lastPress = millis();
    //     lastButtonState = buttonState;
    // }
    

            //fadeDisplay(10, 20, true, leds);
            //writeFormattedTime(getActiveBuffer(), count);
            
	//backgroundSolidColor(getActiveBuffer(), hue, 255, 0);

	
	backgroundSnow(getActiveBuffer(), 20, 0, 2, spawn_snow);
	
	
	if(christmas_alternate){
		textSolidColor(getActiveBuffer(), 0, 240, 255);
	}
	else{
		textSolidColor(getActiveBuffer(), 96, 240, 255);
	}
	

	displayTextBuffer(getActiveBuffer(), textbuffer1, count1, 0, 100);
	fadeDisplay(7, 10, true, leds);
	//drawDisplay(getActiveBuffer(), leds);
	//FastLED.delay(10);
	count1--;
	if(count1 < -200){
		count1 = 27;
		christmas_alternate = !christmas_alternate;
	}
	if((count1 < 27) && (count1 > -82)){
		spawn_snow = false;
	}
	else{
		spawn_snow = true;
	}

	//hue+= 10;

    //Serial.println(mode);

    



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