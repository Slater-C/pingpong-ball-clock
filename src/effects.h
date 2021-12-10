#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <FastLED.h>
#include "display.h"

void backgroundSnow(displayBuffer* buffer, uint8_t snow_rate, int wind_speed, int snow_delay, bool spawn_snow);