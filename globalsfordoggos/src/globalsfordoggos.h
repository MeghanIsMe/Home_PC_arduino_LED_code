/* **********************************************************

	FILE: globalsfordoggos.h -
Contains global constants and variables related to aRGB lighting code  
Variables are declared here but defined in globalsfordoggos.cpp to avoid
multiple definitions coming from including this header too many times
(though I'm not actually sure why that's a problem when the constexpr statements in 
here don't result in multiple definitions).

	AUTHOR: Meghan Allen

	DEPENDENCIES:
FastLED.h - required for CRGB datatype

	ASCII fonts for large comments: 
https://www.asciiart.eu/text-to-ascii-art - pagga from ASCII art archive - medium header
************************************************************/

// include guard statements
#ifndef globalsfordoggos_h
#define globalsfordoggos_h

// dependancy inclusions
#include "FastLED.h"	// required for CRGB data types - backend that interfaces with the hardware

						// ░█▀▀░█░░░█▀█░█▀▄░█▀█░█░░░░░█▀▀░█▀█░█▀█░█▀▀░▀█▀░█▀█░█▀█░▀█▀░█▀▀
						// ░█░█░█░░░█░█░█▀▄░█▀█░█░░░░░█░░░█░█░█░█░▀▀█░░█░░█▀█░█░█░░█░░▀▀█
						// ░▀▀▀░▀▀▀░▀▀▀░▀▀░░▀░▀░▀▀▀░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░░▀░░▀░▀░▀░▀░░▀░░▀▀▀

// ░█▀▀░█▀█░█▀█░█▀▀░▀█▀░█▀█░█▀█░▀█▀░░░▀█▀░█▀█░▀█▀░█▀▀░█▀▀░█▀▀░█▀▄░█▀▀
// ░█░░░█░█░█░█░▀▀█░░█░░█▀█░█░█░░█░░░░░█░░█░█░░█░░█▀▀░█░█░█▀▀░█▀▄░▀▀█
// ░▀▀▀░▀▀▀░▀░▀░▀▀▀░░▀░░▀░▀░▀░▀░░▀░░░░▀▀▀░▀░▀░░▀░░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀

// When constants are defined in a source (.cpp) file, they cannot be used as compile-time constants, so they will not work as array bounds definitions
// so, they must be in the header (.h) file. | Some of these are used for array definitions and the defintion must be here.
// See - https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/
// See also - https://stackoverflow.com/questions/38890349/constexpr-vs-extern-const-which-has-priority#:~:text=Using%20extern%20const%20in%20the,or%20as%20an%20array%20size.

// Aspect fan specs
constexpr int NUMASPECTFANS = 3;
constexpr int ASPECTFANLEDS = 6;
// CPU fan specs
constexpr int NUMCPUFANS = 1;
constexpr int CPUFANLEDS = 4;
// Linear Strip Specs
constexpr int NUMLINEARSTRIPS = 1;
constexpr int LINEARSTRIPLEDS = 20;

// ░█▀▀░█▀█░█▀█░█▀▀░▀█▀░█▀█░█▀█░▀█▀░░░█▀▀░█▀▄░█▀▀░█▀▄░█▀▀
// ░█░░░█░█░█░█░▀▀█░░█░░█▀█░█░█░░█░░░░█░░░█▀▄░█░█░█▀▄░▀▀█
// ░▀▀▀░▀▀▀░▀░▀░▀▀▀░░▀░░▀░▀░▀░▀░░▀░░░░▀▀▀░▀░▀░▀▀▀░▀▀░░▀▀▀
//Could conceivably move these into a library that includes stuff needed for classes related to lighting?

const CRGB NICEBLUE = CRGB(0, 120, 255);
const CRGB TRANSBLUE = CRGB(91,206,250);
const CRGB TRANSPINK = CRGB(245,169,184); 
const CRGB TRANSWHITE = CRGB(128,128,128);
const CRGB BLACK = CRGB::Black;

// ░█▀▀░█▀█░█▀█░█▀▀░▀█▀░█▀█░█▀█░▀█▀░░░█▀▀░█▀▄░█▀▀░█▀▄░░░█▀█░█▀▄░█▀▄░█▀█░█░█░█▀▀
// ░█░░░█░█░█░█░▀▀█░░█░░█▀█░█░█░░█░░░░█░░░█▀▄░█░█░█▀▄░░░█▀█░█▀▄░█▀▄░█▀█░░█░░▀▀█
// ░▀▀▀░▀▀▀░▀░▀░▀▀▀░░▀░░▀░▀░▀░▀░░▀░░░░▀▀▀░▀░▀░▀▀▀░▀▀░░░░▀░▀░▀░▀░▀░▀░▀░▀░░▀░░▀▀▀

// TEST COLOR ARRAYS/PALETTES
const CRGB rgbTest[] = {CRGB::Red, CRGB::Lime, CRGB::Blue, CRGB::Black};
const CRGB redBlueTest[] = {CRGB::Red, CRGB::Blue, CRGB::Black};

// SINGLE COLOR ARRAYS
const CRGB blackForRandom[] = {CRGB::Black};
const CRGB singleGreen[] = {CRGB::Green, CRGB::Black};
const CRGB singlePurple[] = {CRGB::Purple, CRGB::Black};

// ARRAYS OF SINGLE COLOR PLUS ALMOST-BLACK TO USE FOR BREATHING EFFECT WITH FADETHROUGHCOLORS
const CRGB pinkBreathing[] = {CRGB::HotPink, CRGB(0,0,1), CRGB::Black};

// PRIDE COLOR ARRAYS
const CRGB prideBisexual[] = {CRGB(214,2,112), CRGB(155,79,150), CRGB(0,56, 168), CRGB::Black};
const CRGB prideBisexualBreak[] = {CRGB(214,2,112), CRGB(155,79,150), CRGB(0,56, 168), CRGB(0,0,1), CRGB::Black};
const CRGB prideRainbow[] = {CRGB(228,3,3),CRGB(255,140,0),CRGB(255,237,0),CRGB(0,128,38),CRGB(26,64,142),CRGB(115,41,130),CRGB::Black};
const CRGB prideTransgender[] = {CRGB::Turquoise, CRGB::DeepPink, CRGB::Linen, CRGB::DeepPink, CRGB::Black};
const CRGB prideTransgenderBreak[] = {CRGB::Turquoise, CRGB::DeepPink, CRGB::Linen, CRGB::DeepPink, CRGB::Turquoise, CRGB(0,0,1), CRGB::Black};
const CRGB prideLesbian[] = {CRGB(214,46,2),CRGB(184, 60, 8),CRGB(253,152,85),CRGB(125,38,87),CRGB(125,5,82),CRGB::Black};
const CRGB prideLesbianBreak[] = {CRGB(214,46,2),CRGB(184, 60, 8),CRGB(253,152,85),CRGB(125,38,87),CRGB(125,5,82),CRGB(0,0,1),CRGB(0,0,1),CRGB::Black};

						// ░█▀▀░█░░░█▀█░█▀▄░█▀█░█░░░░░█░█░█▀█░█▀▄░▀█▀░█▀█░█▀▄░█░░░█▀▀░█▀▀
						// ░█░█░█░░░█░█░█▀▄░█▀█░█░░░░░▀▄▀░█▀█░█▀▄░░█░░█▀█░█▀▄░█░░░█▀▀░▀▀█
						// ░▀▀▀░▀▀▀░▀▀▀░▀▀░░▀░▀░▀▀▀░░░░▀░░▀░▀░▀░▀░▀▀▀░▀░▀░▀▀░░▀▀▀░▀▀▀░▀▀▀

// These are defined in .cpp file. Declaring here as extern allows this header to be included in multiple files without duplicate defiitions.
// See - https://stackoverflow.com/questions/14526153/multiple-definition-of-a-global-variable
 
extern unsigned long deltaMillis;   

#endif