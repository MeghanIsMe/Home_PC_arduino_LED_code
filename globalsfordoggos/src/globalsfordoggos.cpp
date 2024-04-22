/* **********************************************************
	FILE: globalsfordoggos.cpp
Contains Definitions for variables and constants declared in globalsfordoggos.h
CRGB datatype relies on FastLED library
	
	AUTHOR: Meghan Allen

	ASCII font for large comments: 		
https://www.asciiart.eu/text-to-ascii-art - pagga	
************************************************************/

#include "globalsfordoggos.h" // include this source file's header

//#include "classesfordoggos.h"

// ░█▀▀░█░░░█▀█░█▀▄░█▀█░█░░░░░█░█░█▀█░█▀▄░▀█▀░█▀█░█▀▄░█░░░█▀▀░█▀▀
// ░█░█░█░░░█░█░█▀▄░█▀█░█░░░░░▀▄▀░█▀█░█▀▄░░█░░█▀█░█▀▄░█░░░█▀▀░▀▀█
// ░▀▀▀░▀▀▀░▀▀▀░▀▀░░▀░▀░▀▀▀░░░░▀░░▀░▀░▀░▀░▀▀▀░▀░▀░▀▀░░▀▀▀░▀▀▀░▀▀▀
 
// exists to track the amount of milliseconds passed between the previous main loop execution and the current one
unsigned long deltaMillis = 0; 