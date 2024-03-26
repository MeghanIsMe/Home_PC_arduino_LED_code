/*
  classesfordoggos.h - library for classes related to LED control for Arduino
  relies on FastLED library
*/
#ifndef functionsfordoggos_h
#define functionsfordoggos_h

#include "Arduino.h"
#include "FastLED.h"
#include "classesfordoggos.h"

extern unsigned long deltaMillis;   // milliseconds passed since last main loop execution : defined in puppygirllightingtoy.ino
																		//extern tag required to let functions and methods in this file see individual global variables
//extern const int LARGEFANLEDS;


// UTILITY FUNCTION
//void 
int GetLengthOfBlackTerminatedCRGBArray(CRGB *arr); // overload this for more array types if necessary
void PrintColorArray(CRGB *arr, int length);
void SerialPrintColor(CRGB color);
void SerialPrintVars(int, int, int, int, int);
void WriteAspectFanToHardware(int deviceNumber, CRGB* effectsArray);


// COLOR FUNCTIONS
CRGB MakeRandomColor();
CRGB CheckForRandomColor(CRGB color, CRGB savedColor, int FRAMELIMIT, int frameNumber, int speed);

#endif