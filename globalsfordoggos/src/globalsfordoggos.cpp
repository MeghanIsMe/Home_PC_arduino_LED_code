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
 
// exists to track the amount of milliseconds passed between the previous main loop execution and the current one
unsigned long deltaMillis = 0; 