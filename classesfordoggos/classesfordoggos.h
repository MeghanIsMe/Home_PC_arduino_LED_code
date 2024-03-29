/*
  classesfordoggos.h - library for classes related to LED control for Arduino
  relies on FastLED library
*/
#ifndef classesfordoggos_h
#define classesfordoggos_h

#include "Arduino.h"
#include "FastLED.h"
#include "functionsfordoggos.h"

//extern unsigned long deltaMillis;   // milliseconds passed since last main loop execution
																		//extern tag required to let functions and methods in this file see individual global variables

// ░█▀▀░█▀▀░█▀█░█▀▀░█▀▄░▀█▀░█▀▀░░░█░░░█▀▀░█▀▄░░░█▀▄░█▀▀░█░█░▀█▀░█▀▀░█▀▀░░░█▀▀░█░░░█▀█░█▀▀░█▀▀
// ░█░█░█▀▀░█░█░█▀▀░█▀▄░░█░░█░░░░░█░░░█▀▀░█░█░░░█░█░█▀▀░▀▄▀░░█░░█░░░█▀▀░░░█░░░█░░░█▀█░▀▀█░▀▀█
// ░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░▀▀░░░░▀▀░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀
class generic_LedDevice
{
	public:
	
	int accumulatedMilliseconds; 		// running total of milliseconds passed since last time an effects function executed on this object
	int frameNumber;								// which frame of the animation is currently being displayed on this object by an effects function
	int NUMLEDS;										// how many LEDS are on this device. This should never change once set by a child class
	int paletteColorIndex = 0; 			// for managing use of palette arrays passed to calling effects functions
	bool initializedFrame;   				// whether frameNumber has been set to a specific starting frame
	bool initializedColor; 					// whether paletterColorIndex has been set to a specific starting frame
	CRGB savedColor;								// what color is currently being used to display the effects function on this object
	
	int* p_activeFrameCounter = &frameNumber;				// for effects that need multiple timers, these pointers allow the
	int* p_activeTimer = &accumulatedMilliseconds;  // calling function to choose the appropriate frame and millisecond counters
	
				

	generic_LedDevice()							// constructor function
	{}
	
	//mangement functions
	void CheckInitialization(); 									// Check whether to initialize frame number
	bool CheckTimeForFrameDraw(int speed, int *counter);				// Check whether enough time has passed to update effect
	void AdvanceColor(const CRGB*, int, int);  // acts on savedColor and paletteColorIndex to progress color
	void AdvanceFrame(int speed, int FRAMELIMIT); // acts on p_activeFrameCounter to progress frame number	
	
	//effects functions
			
};


// ░█▀▀░█▀▀░█▀█░█▀▀░█▀▄░▀█▀░█▀▀░░░█▀▀░█▀█░█▀█░░░█▀▀░█░░░█▀█░█▀▀░█▀▀
// ░█░█░█▀▀░█░█░█▀▀░█▀▄░░█░░█░░░░░█▀▀░█▀█░█░█░░░█░░░█░░░█▀█░▀▀█░▀▀█
// ░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░░░▀░░░▀░▀░▀░▀░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀
// parent class for all specific hardware fans (2 at this time: Aspect with 6 LEDs and a CPU fan with 4 LEDs)

//generic_Fan CLASS DECLARATION
class generic_Fan : public generic_LedDevice									
{
	public:
	
	CRGB leds[6];										// holds CRGB values that will be written by an effects function, then written out to the display hardware at end of main loop
	int fanNumber;									// to use when calling methods from systemleds to tell systemleds which fan it is and which memberfan to use
		
	generic_Fan()										// constructor function
	{}	
	
	// utility functions
	void CopyToExternalArray(CRGB*);									 // copies contents of this objects leds array to an external CRGB array
	
	// effects functions
	void BlankFan();																	 // Set all LEDs to black
	void BlinkLeds(int speed, CRGB* palette); 				 // blink all LEDs the same color following passed palette
	void FadeThroughColors(int,const CRGB*);  				 // fades one color into the next progressing through a palette
	void FillFan(CRGB color);	 												 // Fill all LEDs on fan with passed color
	void SpinColorWave(int, const CRGB*);			 				 // Waves of color rotate around fan
	void SpinColorWaveFade(int, const CRGB*, float);	
	void SpinLeds(int, CRGB, CRGB = CRGB::Black, CRGB = CRGB::Black);  //Spin 1-3 LEDs around a fan
	void SpinOneLed(int speed, CRGB* palette);  			 // One LED rotates around fan
	void MovingLine(int speed, CRGB* palette);				 // Line of LEDs bounces back and forth across fan
	
	
};

// ░█▀▀░█▀█░█░█░░░█▀▀░█▀█░█▀█░░░█▀▀░█░░░█▀█░█▀▀░█▀▀
// ░█░░░█▀▀░█░█░░░█▀▀░█▀█░█░█░░░█░░░█░░░█▀█░▀▀█░▀▀█
// ░▀▀▀░▀░░░▀▀▀░░░▀░░░▀░▀░▀░▀░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀
// the fan on the CPU cooler
class cpu_Fan: public generic_Fan							
{
  public:   

  cpu_Fan()                                   // constructor function
  {
		NUMLEDS = 4;															// number of LEDs on the device
		initializedFrame = 0;											// whether starting frame is initialized
		initializedColor = 0;											// whether starting color is initialized
	};  
};

// ░█▀█░█▀▀░█▀█░█▀▀░█▀▀░▀█▀░░░█▀▀░█▀█░█▀█░░░█▀▀░█░░░█▀█░█▀▀░█▀▀
// ░█▀█░▀▀█░█▀▀░█▀▀░█░░░░█░░░░█▀▀░█▀█░█░█░░░█░░░█░░░█▀█░▀▀█░▀▀█
// ░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░░▀░░░░▀░░░▀░▀░▀░▀░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀
// the fans in the computer case on the front and back
class aspect_Fan: public generic_Fan					
{
  public:
  
	aspect_Fan()																// constructor function
	{
		NUMLEDS = 6;															// number of LEDs on the device
		initializedFrame = 0;											// whether starting frame is initialized
		initializedColor = 0;											// whether starting color is initialized		
	};
	//method declarations
	//void CopyToExternalArray(CRGB*);
};

// ░█▀▄░█░█░█▀█░█░░░░░█▀▀░█▀▄░█▀█░█▀█░▀█▀░░░█▀█░█▀▀░█▀█░█▀▀░█▀▀░▀█▀░░░█▀▀░█░░░█▀█░█▀▀░█▀▀
// ░█░█░█░█░█▀█░█░░░░░█▀▀░█▀▄░█░█░█░█░░█░░░░█▀█░▀▀█░█▀▀░█▀▀░█░░░░█░░░░█░░░█░░░█▀█░▀▀█░▀▀█
// ░▀▀░░▀▀▀░▀░▀░▀▀▀░░░▀░░░▀░▀░▀▀▀░▀░▀░░▀░░░░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░░▀░░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀


class dual_FrontAspectFans: public generic_Fan
{
	public:	
	
	int topFrameNumber = 0;
	int bottomFrameNumber = 0;
	int topAccumulatedMillis = 0;
	int bottomAccumulatedMillis = 0;		
	int ledOrder[2][ASPECTFANLEDS];
	CRGB dualFans[2][ASPECTFANLEDS];
	CRGB leds[12]; 
	
	int leftCount = 0; 			// for tracking progress of StackFill
	int leftSubCount = 0; 	// for tracking progress of StackFill
	int rightCount = 0;   	// for tracking progress of StackFill
	int rightSubCount = 0;	// for tracking progress of StackFill
	bool activeSide = 0;  	// for tracking progress of StackFill
	
	dual_FrontAspectFans()								// constructor function
	{
		NUMLEDS = ASPECTFANLEDS * 2;		
	}
	
	// utility functions
	int FindHighestLitLed(bool);
	void TranslateLedsToOutPutArray();
	
	// effects function
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

// ░█▀▀░█▀▄░█▀█░█▀█░▀█▀░░░█░░░█▀▀░█▀▄░░░█▀▀░▀█▀░█▀▄░▀█▀░█▀█░░░█▀▀░█░░░█▀█░█▀▀░█▀▀
// ░█▀▀░█▀▄░█░█░█░█░░█░░░░█░░░█▀▀░█░█░░░▀▀█░░█░░█▀▄░░█░░█▀▀░░░█░░░█░░░█▀█░▀▀█░▀▀█
// ░▀░░░▀░▀░▀▀▀░▀░▀░░▀░░░░▀▀▀░▀▀▀░▀▀░░░░▀▀▀░░▀░░▀░▀░▀▀▀░▀░░░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀

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
		initializedFrame = 0;
		initializedColor = 0;
	}
	//utility functions
	void CopyToExternalArray(CRGB*);
	void WriteToOutgoingArray(int side, CRGB* outArray);
	void DetermineTimer(bool tl, bool tr, bool bl, bool br);
	
	//effects functions
	void BlankLeds();									// Set all LEDs to black
	void BlinkLeds(int speed, CRGB* palette);  // Blinks all LEDs
	void ChaseWithFade(int, const CRGB*, float, int = 1);
	void FillLeds(CRGB color);
	void ScrollColors(int, const CRGB*, int, bool, bool, bool, bool);	
	void ScrollColorsOnFrontStrips(int, const CRGB*, bool, bool, bool, bool);
	void WriteColorsToOutPutArray(CRGB* outArray, bool tl, bool tr, bool bl, bool br, int vertRows);
};

// ░█▀▀░█░█░█░░░█░░░░░█▀▀░█░█░█▀▀░▀█▀░█▀▀░█▄█░░░█░░░█▀▀░█▀▄░█▀▀░░░█▀▀░█░░░█▀█░█▀▀░█▀▀
// ░█▀▀░█░█░█░░░█░░░░░▀▀█░░█░░▀▀█░░█░░█▀▀░█░█░░░█░░░█▀▀░█░█░▀▀█░░░█░░░█░░░█▀█░▀▀█░▀▀█
// ░▀░░░▀▀▀░▀▀▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░░▀░░▀▀▀░▀░▀░░░▀▀▀░▀▀▀░▀▀░░▀▀▀░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀
class full_SystemLeds
{
	public:
	
	// create array members to hold colors for all Aspect fans in the system
	CRGB aspectFansLeds[NUMASPECTFANS][ASPECTFANLEDS];				// aspect fans
	CRGB cpuFanLeds[NUMCPUFANS][CPUFANLEDS];									// cpu fans
	CRGB linearStripLeds[NUMLINEARSTRIPS][LINEARSTRIPLEDS];		// linear strips
	// create arrays for other virtual objects	
	CRGB combined2AspectFans[ASPECTFANLEDS * 2];							// combination of two front Aspect fans
	
	// create two virtual fans for each physical one, allowing blending of effect
	aspect_Fan virtualAspectFan[NUMASPECTFANS * 2];					
	cpu_Fan virtualCPUFan[NUMCPUFANS * 2];
	front_LedStrip virtualLedStrip[NUMLINEARSTRIPS * 2];
	// will need to add linear strip and combined front fan members
	
	full_SystemLeds()																				// constructor function
	{
		// set all leds in array members to black
		for (int i = 0; i < NUMASPECTFANS; i++)
			for (int j = 0; j < ASPECTFANLEDS; j++)
				aspectFansLeds[i][j] = CRGB::Black;
		for (int i = 0; i < NUMCPUFANS; i++)
			for (int j = 0; j < CPUFANLEDS; j++)
				cpuFanLeds[i][j] = CRGB::Black;
		for (int i = 0; i < NUMLINEARSTRIPS; i++)
			for (int j = 0; j < LINEARSTRIPLEDS; j++)
				linearStripLeds[i][j] = CRGB::Black;		
	}

	void CopyFanToExternalArray(int, CRGB*);
	void CopyAspectFanToExternalArray(int, CRGB*);
	void TranslateCombinedAspectsToIndividualFans(int,int);  //translates a populated combined2AspectFans array into 2 separate 1-dimension elements of aspectFansLeds

};

// instance of full_SystemLeds for the program to use in maniuplating and writing colors
extern full_SystemLeds systemLeds; /* declared/defined here because it needs to be accessible
	by various classes in classesfordoggos, but it can't be defined in globalsfordoggos because
	it relies on the full_SystemLeds class which is defined in classesfordoggos. I tried 
	#includinging classesfordoggos.h in the global files, but that gave me duplicate definition
	problems.  */

#endif