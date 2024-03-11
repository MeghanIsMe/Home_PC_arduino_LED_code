/*
  classesfordoggos.h - library for classes related to LED control for Arduino
  relies on FastLED library
*/
#ifndef classesfordoggos.h
#define classesfordoggos.h

#include "Arduino.h"
#include "FastLED.h"
#include "functionsfordoggos.h"

///////////////////
//CPU FAN CLASS////
///////////////////

//generic_Fan CLASS DECLARATION
class generic_Fan
{
	public:
	
	int accumulatedMilliseconds;
	int frameNumber;
	int NUMLEDS;
	bool initialized;   
	CRGB savedColor;
	CRGB leds[6];
		
	generic_Fan()
	{}
	
	//mangement functions
	void AddElapsedTimeToTotal(int deltaMillis);
	void CheckInitialization(); 
	bool CheckTimeForFrameDraw(int speed);
	void FrameAdvance(int speed, int FRAMELIMIT);
	
	//effects functions
	void BlankFan();
	void SpinOneLed(int speed, CRGB color);  
	//void SpinLeds(int speed, CRGB color);
};

//cpu_Fan CLASS DECLARATION
class cpu_Fan: public generic_Fan
{
  public:   

  cpu_Fan()                                   // constructor function
  {
		NUMLEDS = 4;
		initialized = 0;
	};  
};

//aspect_Fan CLASS DECLARATION
class aspect_Fan: public generic_Fan
{
  public:
  
	aspect_Fan()
	{
		NUMLEDS = 6;
		initialized = 0;
	};
};


#endif