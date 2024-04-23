/* **********************************************************
	FILE: main.cpp
Contains driving code for running aRGB effects on hardware configured on my desktop PC case.

	AUTHOR: Meghan Allen

	ASCII fonts for large comments: 
https://www.asciiart.eu/text-to-ascii-art - pagga

	TO-DOs
Add default speeds (and other default values like fade percentage in SpinColorWaveFade)
************************************************************/

// dependancy inclusions
#include "FastLED.h"				// for backend hardware interfacing
#include "globalsfordoggos.h"		// global settings like number of leds per type of fan and similar
#include "ledcontrolfordoggos.h"	// classes and functions that support and control the lighting effects

// constants to make it easier to see what pin is being used by FastLED to connect to arrays
// this is based on hardware setup - how many and what kind of LEDs are connected to the controller
// is fixed by hardware configuration
#define DATA_PIN2 2
#define DATA_PIN4 4
#define DATA_PIN5 5
#define DATA_PIN7 7
#define DATA_PIN8 8
#define DATA_PIN9 9

// These are the arrays that are written to hardware by FastLED.show at the end of each main loop
// They have a 1-1 correspondence to the aRGB LED hardware
CRGB stripLeds[LINEARSTRIPLEDS];	// front LED strip is on pin 9
CRGB aspect0Leds[ASPECTFANLEDS];	// front bottom fan is on pin 2
CRGB aspect1Leds[ASPECTFANLEDS];	// front top fan is on pin 4
CRGB aspect2Leds[ASPECTFANLEDS];	// back case fan is on pin 8
CRGB cpuFanLeds[CPUFANLEDS];		// CPU fan is on pin 7

// Instantiating the object that does most of the work of setting LED colors
full_SystemLeds systemLeds;
// Instantiating the system timer
system_Timer systemTimer;

void setup() 
{
	delay(8000);			// power on safety delay
	Serial.begin(9600);		// for serial debugging

	// Associating arrays with FastLED. These arrays will be written out to hardware at the end of each main loop
	FastLED.addLeds<WS2812B, DATA_PIN2, GRB>(aspect0Leds,6);	// aspect0Leds array (bottom front fan) is on pin 2
	FastLED.addLeds<WS2812B, DATA_PIN4, GRB>(aspect1Leds,6);	// aspect1Leds array (top front fan) is on pin 4
	FastLED.addLeds<WS2812B, DATA_PIN8, GRB>(aspect2Leds,6);	// aspect2Leds array (back case fan) is on pin 8
	FastLED.addLeds<WS2812B, DATA_PIN7, GRB>(cpuFanLeds,4);		// cpuFanLeds array (CPU fan) is on pin 7
	FastLED.addLeds<WS2812B, DATA_PIN9, GRB>(stripLeds,20);		// stripLeds array (front LED strip) is on pin 9
 }

void loop() {

	systemTimer.UpdateSystemTimer();			// have the system timer object find time passed since last main loop execution
	deltaMillis = systemTimer.GetDeltaMillis();	// deltaMillis is defined in globals for doggos. It is global so that all classes have access to the value for use in timing

	systemLeds.virtualAspectFan[2].FadeThroughColors(2000, pinkBreathing);
	systemLeds.virtualDualAspectFans[0].MovingLineDualAspect(-100, prideLesbian);


	//systemLeds.virtualAspectFan[2].SpinOneLed(60, prideTransgender );

	systemLeds.virtualCPUFan[0].FadeThroughColors(3000,pinkBreathing);

	//systemLeds.virtualLedStrip[0].ChaseWithFade(60,prideTransgender, .6,2);

	systemLeds.virtualLedStrip[0].ScrollColorsOnFrontStrips(300, prideLesbian, 1,0,1,0);
	systemLeds.virtualLedStrip[0].ScrollColorsOnFrontStrips(-300, prideTransgender, 0,1,0,1);
	//systemLeds.virtualLedStrip[0].BlinkLeds(200,prideTransgender);

	// I feel like it makes the most intuitive sense to make methods of the systemleds object copy arrays out to hardware-associated arrays instead of
	// using individual fan object methods. It feels more like the system leds device is managing system operations and is separated froom the indvidual
	// hardware objects
	// I think I want to rewrite it that way
	//systemLeds.virtualAspectFan[0].CopyToExternalArray(aspect0Leds);
	//systemLeds.virtualAspectFan[1].CopyToExternalArray(aspect1Leds);
	systemLeds.virtualDualAspectFans[0].CopyToTwoExternalArrays(aspect1Leds, aspect0Leds);
	systemLeds.virtualAspectFan[2].CopyToExternalArray(aspect2Leds);

	systemLeds.virtualCPUFan[0].CopyToExternalArray(cpuFanLeds);

	systemLeds.virtualLedStrip[0].CopyToExternalArray(stripLeds);

	FastLED.show();     
}