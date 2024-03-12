/*
  classesfordoggos.h - library for classes related to LED control for Arduino
  relies on FastLED library
*/
#ifndef classesfordoggos.h
#define classesfordoggos.h

#include "Arduino.h"
#include "FastLED.h"
#include "functionsfordoggos.h"

extern unsigned long deltaMillis;   // milliseconds passed since last main loop execution
																		//extern tag required to let functions and methods in this file see individual global variables

///////////////////////
// GENERIC FAN CLASS //  
///////////////////////
// parent class for all specific hardware fans (2 at this time: Aspect with 6 LEDs and a CPU fan with 4 LEDs)

//generic_Fan CLASS DECLARATION
class generic_Fan									
{
	public:
	
	int accumulatedMilliseconds; 		// running total of milliseconds passed since last time an effects function executed on this object
	int frameNumber;								// which frame of the animation is currently being displayed on this object by an effects function
	int NUMLEDS;										// how many LEDS are on this device. This should never change
	bool initialized;   						// whether frameNumber has been set to a specific starting frame
	CRGB savedColor;								// what color is currently being used to display the effects function on this object
	CRGB leds[6];										// holds CRGB values that will be written by an effects function, then written out to the display hardware at end of main loop
		
	generic_Fan()										// constructor function
	{}
	
	//mangement functions
	void CheckInitialization(); 
	bool CheckTimeForFrameDraw(int speed);
	void FrameAdvance(int speed, int FRAMELIMIT);
	
	//effects functions
	void BlankFan();
	void SpinColorWave(int speed);
	void SpinLeds(int, CRGB, CRGB color2 = CRGB::Black, CRGB color3 = CRGB::Black);
	void SpinOneLed(int speed, CRGB color);  
	void generic_Fan::MovingLine(int speed, CRGB color);

	
};

/////////////////////
// CPU FAN CLASS ////
/////////////////////
// the fan on the CPU cooler
class cpu_Fan: public generic_Fan							
{
  public:   

  cpu_Fan()                                   // constructor function
  {
		NUMLEDS = 4;
		initialized = 0;
	};  
};

//////////////////////
// ASPECT FAN CLASS //
//////////////////////
// the fans in the computer case on the front and back
class aspect_Fan: public generic_Fan					
{
  public:
  
	aspect_Fan()																// constructor function
	{
		NUMLEDS = 6;
		initialized = 0;
	};
};


#endif