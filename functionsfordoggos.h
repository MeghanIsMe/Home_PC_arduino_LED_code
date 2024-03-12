/*
  classesfordoggos.h - library for classes related to LED control for Arduino
  relies on FastLED library
*/
#ifndef functionsfordoggos.h
#define functionsfordoggos.h

#include "Arduino.h"
#include "FastLED.h"
#include "classesfordoggos.h"

extern unsigned long deltaMillis;   // milliseconds passed since last main loop execution
																		//extern tag required to let functions and methods in this file see individual global variables

void SerialPrintColor(CRGB color);
CRGB MakeRandomColor();
CRGB CheckForRandomColor(CRGB color, CRGB savedColor, int FRAMELIMIT, int frameNumber, int speed);

#endif