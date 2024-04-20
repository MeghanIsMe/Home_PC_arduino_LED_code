/*
  globalsfordoggos.cpp - definitions for variables and constants declared in globalsfordoggos.h
  CRGB datatyle relies on FastLED library
*/

#include "FastLED.h" // required for CRGB datatype
#include "globalsfordoggos.h"

//#include "classesfordoggos.h"

// ░█▀▀░█░░░█▀█░█▀▄░█▀█░█░░░░░█░█░█▀█░█▀▄░▀█▀░█▀█░█▀▄░█░░░█▀▀░█▀▀
// ░█░█░█░░░█░█░█▀▄░█▀█░█░░░░░▀▄▀░█▀█░█▀▄░░█░░█▀█░█▀▄░█░░░█▀▀░▀▀█
// ░▀▀▀░▀▀▀░▀▀▀░▀▀░░▀░▀░▀▀▀░░░░▀░░▀░▀░▀░▀░▀▀▀░▀░▀░▀▀░░▀▀▀░▀▀▀░▀▀▀

// TIMING VARIABLES - At the beginning of each main loop:
//		pastMillis is updated to currentMillis
//		currentMillis is updated to total milliseconds since power on
//		deltaMillis is the difference between them, used for timing by numerous functions


//unsigned long currentMillis = 0;  
//unsigned long pastMillis = 0;     
unsigned long deltaMillis = 0; // exists to track the amount of milliseconds passed between the previous main loop execution and the current one


// Arrays for holding color data
CRGB largeFans[NUMASPECTFANS][ASPECTFANLEDS];  // The color data for Aspect fans that will be written out to hardware at end of main loop