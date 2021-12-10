#include "effects.h"
#include "display.h"
#include "characters.h"
#include <cstddef>

void backgroundSnow(displayBuffer* buffer, uint8_t snow_rate, int wind_speed, int snow_delay, bool spawn_snow){

	static bool snow_particle[133] = {0};
	static int delay_count = 0;
	
	if((delay_count >= snow_delay) && spawn_snow){
			for(int i = 0; i < 19; i++){
				if(random(255) < snow_rate){
					snow_particle[i] = 1;
				}
			}
	}

	for (int i = 0; i < 133; i++){
		buffer->layer2[i].hue = 160;
		buffer->layer2[i].sat = 20;
		if(snow_particle[i]){
			buffer->layer2[i].val = 255;
			buffer->layer2[i].transparent = false;
		}
		else{
			buffer->layer2[i].val = 0;
			buffer->layer2[i].transparent = true;
		}
		//Serial.print("Particle "); Serial.print(i); Serial.print(" :"); Serial.println(snow_particle[i]); 
	}

	if(delay_count >= snow_delay){
		for(int y = 6; y >= 0; y--){
			for(int x = 0; x < 19; x++){
				//Serial.print("Index "); Serial.println(getIndex(x, y));
				if(snow_particle[getIndex(x, y)]){
					snow_particle[getIndex(x, y)] = false;
					if(y != 6){
						snow_particle[getIndex(x+(2*(x%2)-1)+wind_speed, y+1)] = true; // Copy snow particle to next line, make it wobble left and right
					}
					else{
						snow_particle[getIndex(x, y)] = false;
					}
					//Serial.print("New loc "); Serial.println(getIndex(x+(x%1)+wind_speed, y+1));
				}
			}
		}
		delay_count = 0;
	}

	
	delay_count++;
	

}