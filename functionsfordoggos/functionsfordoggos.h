/*
  classesfordoggos.h - library for classes related to LED control for Arduino
  relies on FastLED library
*/
#ifndef functionsfordoggos.h
#define functionsfordoggos.h

#include "Arduino.h"
#include "FastLED.h"
#include "classesfordoggos.h"

CRGB MakeRandomColor();
CRGB CheckForRandomColor(CRGB color, CRGB savedColor, int FRAMELIMIT, int frameNumber, int speed);

#endif