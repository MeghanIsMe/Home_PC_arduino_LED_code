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

////////////////////////////////
// GENERIC LED DEVICE CLASS ////  
////////////////////////////////
class generic_LedDevice
{
	public:
	
	int accumulatedMilliseconds; 		// running total of milliseconds passed since last time an effects function executed on this object
	int frameNumber;								// which frame of the animation is currently being displayed on this object by an effects function
	int NUMLEDS;										// how many LEDS are on this device. This should never change once set by a child class
	int paletteColorIndex = 0; 			// for managing use of palette arrays passed to calling effects functions
	bool initialized;   						// whether frameNumber has been set to a specific starting frame
	CRGB savedColor;								// what color is currently being used to display the effects function on this object
	
	int* p_activeFrameCounter = &frameNumber;				// for effects that need multiple timers, these pointers allow the
	int* p_activeTimer = &accumulatedMilliseconds;  // calling function to choose the appropriate frame and millisecond counters
	
				

	generic_LedDevice()							// constructor function
	{}
	
	//mangement functions
	void CheckInitialization(); 									// Check whether to initialize frame number
	bool CheckTimeForFrameDraw(int speed, int *counter);				// Check whether enough time has passed to update effect
	void AdvanceColor(CRGB* palette, int FRAMELIMIT, int speed);
	int AdvanceFrame(int speed, int FRAMELIMIT); // Advance frame number as appropriate
	//effects functions
			
};


///////////////////////
// GENERIC FAN CLASS //  
///////////////////////
// parent class for all specific hardware fans (2 at this time: Aspect with 6 LEDs and a CPU fan with 4 LEDs)

//generic_Fan CLASS DECLARATION
class generic_Fan : public generic_LedDevice									
{
	public:
	
	CRGB leds[6];										// holds CRGB values that will be written by an effects function, then written out to the display hardware at end of main loop
		
	generic_Fan()										// constructor function
	{}	
	
	//effects functions
	void BlankFan();												 // Set all LEDs to black
	void FillFan(CRGB color);	 // Fill all LEDs on fan with passed color
	void SpinColorWave(int speed, CRGB* palette);					 // Waves of color rotate around fan
	void SpinLeds(int, CRGB, CRGB color2 = CRGB::Black, CRGB color3 = CRGB::Black);  //Spin 1-3 LEDs around a fan
	void SpinOneLed(int speed, CRGB color);  // One LED rotates around fan
	void MovingLine(int speed, CRGB color);	 // Line of LEDs bounces back and forth across fan
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
		NUMLEDS = 4;															// number of LEDs on the device
		initialized = 0;													// whether starting frame is initialized
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
		NUMLEDS = 6;															// number of LEDs on the device
		initialized = 0;													// whether starting frame is initialized
	};
};

////////////////////////////////////////
// FRONT LED STRIP CLASS and CHILDREN //  
////////////////////////////////////////
class generic_LedStrip : public generic_LedDevice
{
	public:
	
	generic_LedStrip() {};
	
	// utility functions
};

class front_LedStrip : public generic_LedStrip
{
	public:	

	// for tracking effects running on portions of the object	
	int topLeftFrameNumber = 0;
	int topRightFrameNumber = 0;
	int bottomLeftFrameNumber = 0;
	int bottomRightFrameNumber = 0;
	int topLeftAccumulatedMillis = 0;
	int topRightAccumulatedMillis = 0;
	int bottomLeftAccumulatedMillis = 0;
	int bottomRightAccumulatedMillis = 0;
		
	CRGB leds[20];										// holds CRGB values that will be written by an effects function, then written out to the display hardware at end of main loop
	
	
	front_LedStrip()									// constructor function
	{
		NUMLEDS = 20;										// how many LEDS are on this device. This should never change
		initialized = 0;
	}
	//utility functions
	void WriteToOutgoingArray(int side, CRGB* outArray);
	void DetermineTimer(bool tl, bool tr, bool bl, bool br);
	
	//effects functions
	void BlankLeds();									// Set all LEDs to black
	void BlinkLeds(int speed, CRGB color);  // Blinks all LEDs
	void FillLeds(CRGB color);
	void TransColorsScrollingFrontLeds(int speed, CRGB *palette, int side);
	void ScrollColors(int speed, CRGB* palette,int vertRows, bool tr, bool tl, bool br, bool bl);	
	void ScrollColorsOnFrontStrips(int speed, CRGB* palette, bool tl, bool tr, bool bl, bool br);
	void WriteColorsToOutPutArray(CRGB* outArray, bool tl, bool tr, bool bl, bool br, int vertRows);
};

#endif