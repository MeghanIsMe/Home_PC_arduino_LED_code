/* **********************************************************
	FILE:  ledcontrolfordoggos.h
Header file with declarations for functions and classes used to control ARGB hardware on
my desktop computer. Definitions are in ledcontrolfordoggos.cpp

	AUTHOR: Meghan Allen

	DEPENDENCIES:
FastLED.h - required for CRGB datatype
globalsfordoggos.h - for constant system configuration data, like number of fans, leds, etc.

	ASCII font for large comments: 		
https://www.asciiart.eu/text-to-ascii-art - pagga		
************************************************************/

// include guard statements
#ifndef ledcontrolfordoggos_h
#define ledcontrolfordoggos_h

// dependancy inclusions
#include "FastLED.h"			// required for CRGB data types - backend that interfaces with the hardware
#include "globalsfordoggos.h"	// global settings like number of leds per type of fan and similar

// ░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░░░█▀▄░█▀▀░█▀▀░▀░█▀▀
// ░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░░░█░█░█▀▀░█░░░░░▀▀█
// ░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░░░▀▀░░▀▀▀░▀▀▀░░░▀▀▀
// these are functions directly associated with use of FastLED and this library
// these are defined in ledcontrolfodoggos.cpp (of course)
int GetLengthOfBlackTerminatedCRGBArray(const CRGB*); // overload this for more array types if necessary
void PrintColorArray(CRGB*, int);	// to make printing color array contents for debugging easier
void SerialPrintColor(CRGB);		// to make printing color data for an led for debugging easier

// ░█▀▀░█░░░░░░░█▀▀░█▀▀░█▀█░█▀▀░█▀▄░▀█▀░█▀▀░░░█░░░█▀▀░█▀▄░░░█▀▄░█▀▀░█░█░▀█▀░█▀▀░█▀▀
// ░█░░░█░░░▄▄▄░█░█░█▀▀░█░█░█▀▀░█▀▄░░█░░█░░░░░█░░░█▀▀░█░█░░░█░█░█▀▀░▀▄▀░░█░░█░░░█▀▀
// ░▀▀▀░▀▀▀░░░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░▀▀░░░░▀▀░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀class generic_LedDevice
class generic_LedDevice
{
	public:
	// variables
	int accumulatedMilliseconds; 		// running total of milliseconds passed since last time an effects function executed on this object
	int frameNumber;					// which frame of the animation is currently being displayed on this object by an effects function
	int NUMLEDS;						// how many LEDS are on this device. This should never change once set by a child class
	int paletteColorIndex = 0; 			// for managing use of palette arrays passed to calling effects functions
	bool initializedFrame;   			// whether frameNumber has been set to a specific starting frame
	bool initializedColor; 				// whether paletterColorIndex has been set to a specific starting frame
	CRGB savedColor;					// what color is currently being used to display the effects function on this object
	// pointers
	int* p_activeFrameCounter = &frameNumber;		// for effects that need multiple timers, these pointers allow the
	int* p_activeTimer = &accumulatedMilliseconds;  // calling function to choose the appropriate frame and millisecond counters
	CRGB* p_objectLedArray; 			// will point at a child object's array of LEDs once one is declared
	
	generic_LedDevice()					// constructor function
	{}
	
	//mangement functions
	void CheckInitialization();				// Check whether to initialize frame number
	bool CheckTimeForFrameDraw(int, int*);	// Check whether enough time has passed to update effect
	void CopyToExternalArray(CRGB*);
	void AdvanceColor(const CRGB*, int, int);	// acts on savedColor and paletteColorIndex to progress color
	void AdvanceFrame(int, int); 			// acts on p_activeFrameCounter to progress frame number	
	// effects functions
	void BlankLeds(int);					// sets all of object's leds to black(off)
	void BlinkLeds(int, const CRGB*);		// blink all of objects's leds the same color following palette order
	void LightAllLeds(int, CRGB);
};

// ░█▀▀░█░░░░░░░█▀▀░█▀▀░█▀█░█▀▀░█▀▄░▀█▀░█▀▀░░░█▀▀░█▀█░█▀█
// ░█░░░█░░░▄▄▄░█░█░█▀▀░█░█░█▀▀░█▀▄░░█░░█░░░░░█▀▀░█▀█░█░█
// ░▀▀▀░▀▀▀░░░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░░░▀░░░▀░▀░▀░▀
// parent class for all specific hardware fans (2 at this time: Aspect with 6 LEDs and a CPU fan with 4 LEDs)
class generic_Fan : public generic_LedDevice									
{
	public:	
		
	generic_Fan()									// constructor function
	{}	
	
	// utility functions
		
	// test functions
	
	// effects functions
	void FadeThroughColors(int,const CRGB*);		// fades one color into the next progressing through a palette
	void SpinColorWave(int, const CRGB*);			// Waves of color rotate around fan
	void SpinColorWaveFade(int, const CRGB*, float = .3);	// waves of color rotate around fan and fade out	
	void SpinLeds(int, CRGB, CRGB = BLACK, CRGB = BLACK);	//Spin 1-3 LEDs around a fan
	void SpinOneLed(int, const CRGB*);				// One LED rotates around fan
	void MovingLine(int, const CRGB*);				// Line of LEDs bounces back and forth across fan
	
	
};

// ░█▀▀░█░░░░░░░█▀▀░█▀█░█░█░░░█▀▀░█▀█░█▀█
// ░█░░░█░░░▄▄▄░█░░░█▀▀░█░█░░░█▀▀░█▀█░█░█
// ░▀▀▀░▀▀▀░░░░░▀▀▀░▀░░░▀▀▀░░░▀░░░▀░▀░▀░▀
// the fan on the CPU cooler

class cpu_Fan: public generic_Fan							
{
  public:   

  CRGB leds[CPUFANLEDS];

  cpu_Fan()								// constructor function
  {		
		NUMLEDS = CPUFANLEDS;			// number of LEDs on the device
		initializedFrame = 0;			// whether starting frame is initialized
		initializedColor = 0;			// whether starting color is initialized
		p_objectLedArray = leds;		// initialize array pointer to object's LED array							
	};  
};

// ░█▀▀░█░░░░░░░█▀█░█▀▀░█▀█░█▀▀░█▀▀░▀█▀░░░█▀▀░█▀█░█▀█
// ░█░░░█░░░▄▄▄░█▀█░▀▀█░█▀▀░█▀▀░█░░░░█░░░░█▀▀░█▀█░█░█
// ░▀▀▀░▀▀▀░░░░░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░░▀░░░░▀░░░▀░▀░▀░▀
// the fans in the computer case on the front and back
class aspect_Fan: public generic_Fan					
{
	public:

	CRGB leds[ASPECTFANLEDS];
  
	aspect_Fan()						// constructor function
	{
		NUMLEDS = ASPECTFANLEDS;		// number of LEDs on the device
		initializedFrame = 0;			// whether starting frame is initialized
		initializedColor = 0;			// whether starting color is initialized		
		p_objectLedArray = leds;		// initialize array pointer to object's LED array		
	};
	//method declarations
	//void CopyToExternalArray(CRGB*);
};

// ░█▀▀░█░░░░░░░█▀▄░█░█░█▀█░█░░░░░█▀▀░█▀▄░█▀█░█▀█░▀█▀░░░█▀█░█▀▀░█▀█░█▀▀░█▀▀░▀█▀░░░█▀▀░█▀█░█▀█
// ░█░░░█░░░▄▄▄░█░█░█░█░█▀█░█░░░░░█▀▀░█▀▄░█░█░█░█░░█░░░░█▀█░▀▀█░█▀▀░█▀▀░█░░░░█░░░░█▀▀░█▀█░█░█
// ░▀▀▀░▀▀▀░░░░░▀▀░░▀▀▀░▀░▀░▀▀▀░░░▀░░░▀░▀░▀▀▀░▀░▀░░▀░░░░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░░▀░░░░▀░░░▀░▀░▀░▀
// This is a virtual object used to coordinate effects running on two Aspect fans at the same time
// It leds array has one element for each of the fans, for a total of ASPECTFANLEDS * 2 or 12
class dual_FrontAspectFans: public generic_Fan
{
	public:	
	
	int topFrameNumber = 0;
	int bottomFrameNumber = 0;
	int topAccumulatedMillis = 0;
	int bottomAccumulatedMillis = 0;		
	int ledOrder[2][ASPECTFANLEDS];

	CRGB ledsSeparate[2][ASPECTFANLEDS];
	CRGB leds[ASPECTFANLEDS * 2]; 
	
	int leftCount = 0; 		// for tracking progress of StackFill
	int leftSubCount = 0; 	// for tracking progress of StackFill
	int rightCount = 0;   	// for tracking progress of StackFill
	int rightSubCount = 0;	// for tracking progress of StackFill
	bool activeSide = 0;  	// for tracking progress of StackFill
	
	dual_FrontAspectFans()				// constructor function
	{
		NUMLEDS = ASPECTFANLEDS * 2;	// number of leds controlled by this virtual object
		p_objectLedArray = leds;		// initialize array pointer to object's LED array			
	}
	
	// utility functions
	void CopyToTwoExternalArrays(CRGB*, CRGB*); // copy objects leds to two external arrays
	int FindHighestLitLed(bool);
		
	// effects function
	void MovingLineDualAspect(int, const CRGB*);
	void StackFill(int, const CRGB*);		
	void StackLeft();
	void StackRight();
}; 

// ░█▀▀░█░░░░░░░█▀▀░█▀▀░█▀█░█▀▀░█▀▄░▀█▀░█▀▀░░░█░░░█▀▀░█▀▄░░░█▀▀░▀█▀░█▀▄░▀█▀░█▀█
// ░█░░░█░░░▄▄▄░█░█░█▀▀░█░█░█▀▀░█▀▄░░█░░█░░░░░█░░░█▀▀░█░█░░░▀▀█░░█░░█▀▄░░█░░█▀▀
// ░▀▀▀░▀▀▀░░░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░▀▀░░░░▀▀▀░░▀░░▀░▀░▀▀▀░▀░░

class generic_LedStrip: public generic_LedDevice
{
	public:
	
	generic_LedStrip() {};
	
	// utility functions
};

// ░█▀▀░█░░░░░░░█▀▀░█▀▄░█▀█░█▀█░▀█▀░░░█░░░█▀▀░█▀▄░░░█▀▀░▀█▀░█▀▄░▀█▀░█▀█
// ░█░░░█░░░▄▄▄░█▀▀░█▀▄░█░█░█░█░░█░░░░█░░░█▀▀░█░█░░░▀▀█░░█░░█▀▄░░█░░█▀▀
// ░▀▀▀░▀▀▀░░░░░▀░░░▀░▀░▀▀▀░▀░▀░░▀░░░░▀▀▀░▀▀▀░▀▀░░░░▀▀▀░░▀░░▀░▀░▀▀▀░▀░░
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
		
	CRGB leds[LINEARSTRIPLEDS];			// holds CRGB values that will be written by an effects function, then written out to the display hardware at end of main loop
		
	front_LedStrip()					// constructor function
	{
		NUMLEDS = LINEARSTRIPLEDS;		// how many LEDS are on this device. This should never change
		initializedFrame = 0;
		initializedColor = 0;
		p_objectLedArray = leds;		// initialize array pointer to object's LED array		
	}
	//utility functions
	void WriteToOutgoingArray(int, CRGB*);
	void DetermineTimer(bool, bool, bool, bool);
	
	//effects functions
	
	void ChaseWithFade(int, const CRGB*, float, int = 1); // chasing affect with fading tail
	void ScrollColors(int, const CRGB*, int, bool, bool, bool, bool);
	void ScrollColorsOnFrontStrips(int, const CRGB*, bool, bool, bool, bool);
	void WriteColorsToOutPutArray(CRGB*, bool, bool, bool, bool, int);
};

// ░█▀▀░█░░░░░░░█▀▀░█░█░█░░░█░░░░░█▀▀░█░█░█▀▀░▀█▀░█▀▀░█▄█░░░█░░░█▀▀░█▀▄░█▀▀
// ░█░░░█░░░▄▄▄░█▀▀░█░█░█░░░█░░░░░▀▀█░░█░░▀▀█░░█░░█▀▀░█░█░░░█░░░█▀▀░█░█░▀▀█
// ░▀▀▀░▀▀▀░░░░░▀░░░▀▀▀░▀▀▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░░▀░░▀▀▀░▀░▀░░░▀▀▀░▀▀▀░▀▀░░▀▀▀

class full_SystemLeds
{
	public:
	
	// create two virtual fans for each physical one, allowing blending of effect
	aspect_Fan virtualAspectFan[NUMASPECTFANS * 2];					
	cpu_Fan virtualCPUFan[NUMCPUFANS * 2];
	front_LedStrip virtualLedStrip[NUMLINEARSTRIPS * 2];
	dual_FrontAspectFans virtualDualAspectFans[2];
	// will need to add dual front fan members? Or do we handle that with translations algorithms?

	full_SystemLeds()		// constructor function																			// constructor function
	{ }

	void CopyFanToExternalArray(int, CRGB*);
	void CopyAspectFanToExternalArray(int, CRGB*);
	//void TranslateCombinedAspectsToIndividualFans(int,int);  //translates a populated combined2AspectFans array into 2 separate 1-dimension elements of aspectFansLeds

};

// ░█▀▀░█░░░░░░░█▀▀░█░█░█▀▀░▀█▀░█▀▀░█▄█░░░▀█▀░▀█▀░█▄█░█▀▀░█▀▄
// ░█░░░█░░░▄▄▄░▀▀█░░█░░▀▀█░░█░░█▀▀░█░█░░░░█░░░█░░█░█░█▀▀░█▀▄
// ░▀▀▀░▀▀▀░░░░░▀▀▀░░▀░░▀▀▀░░▀░░▀▀▀░▀░▀░░░░▀░░▀▀▀░▀░▀░▀▀▀░▀░▀

class system_Timer
{
	public:

	unsigned long pastMillis;
	unsigned long currentMillis;
	int deltaMillis;
	
	system_Timer()
	{
		currentMillis = millis();
	}

	void UpdateSystemTimer();
	int GetDeltaMillis();
};

#endif