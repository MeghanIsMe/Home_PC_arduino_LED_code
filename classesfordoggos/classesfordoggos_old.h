/*
  classesfordoggos.h - library for classes related to LED control for Arduino
  relies on FastLED library
*/
#ifndef classesfordoggos.h
#define classesfordoggos.h

#include "Arduino.h"
#include "FastLED.h"

class generic_Fan
{
	public:
	
	generic_Fan()
	{}
};

class aspect_Fan
{
  public:
  const static int NUMLEDS = 6;
  int initialized = 0;
  int deviceNumber;
  CRGB leds[NUMLEDS];

  aspectFan(int deviceNumber)                 // constructor function
  {
    deviceNumber = deviceNumber;
  }
};

class cpu_Fan: public generic_Fan
{
  public:

  const static int NUMLEDS = 4;
  bool initialized = 0;  
  int accumulatedMilliseconds;
  int frameNumber;
  CRGB leds[NUMLEDS];

  cpu_Fan()                                   // constructor function
  {}  ;

  //**********************
  //management functions//
  //**********************
  
  void (
  
  //called by effects function to manage frame write timing.
  bool CheckTimeForFrameDraw(int speed,int deltaMillis)  
  {
    if (speed < 0)                            //convert negative speed to positive for internal comparison.
      speed *= -1;
    accumulatedMilliseconds += deltaMillis;   //add elapsed millis since last function call to running total.   
    if (accumulatedMilliseconds < speed)      //check whether enough time has passed to write the next frame.
      return false;                           //if not, return false.
    else    
    {
      accumulatedMilliseconds = 0;
      return true;                            //if so, return true.
    }
  }

  //called by effects function to see if the frame number is initialized and initialize it if necessary.
  //new fan objects have a non-intialized frame number, so this sets it to 0.
  //could also be used to switch to a different frame number before or while running, possibly. Not implemented yet.
  void CheckInitialization()
  {
    if (!initialized)
    {
      frameNumber = 0;
      initialized = 1;
    }
  }

  //called by effects function to manage frame advancement
  void FrameAdvance(int speed, int FRAMELIMIT)
  {
    if (speed >= 0)                     //with positive speed, frames increment from 0 to FRAMELIMIT
    {    
      frameNumber += 1;
      if (frameNumber == FRAMELIMIT)    //when frameNumber reaches FRAMELIMIT, it resets to 0 before next function iteration
        frameNumber = 0;
    }
    else
    {
      frameNumber -= 1;                 //with negative speed, frames decrement from FRAMELIMIT -1 to -1
      if (frameNumber == -1)
        frameNumber = FRAMELIMIT -1;    //when frameNumber reaches -1, reset to FRAMELIMIT -1 before next function iteration
    }
  }

  //called by effects functions to write the internal output array to the array that gets written to the hardware
  /*
  void WriteColorsToFan()
  {
    for (int i = 0; i < NUMLEDS; i++)  //copy internal array (leds[]) to external array(fan3[]) for writing to hardware at end of main loop
      fan3[i] = leds[i];    
  }
  */

  //*******************
  //effects functions//
  //*******************

  //blank fan - write black (off) to all LEDs on the fan
  //typically called prior to code that writes the current frame to the output array
  void BlankFan()
  {
    for (int i = 0; i < NUMLEDS; i++)
      leds[i] = CRGB::Black;
  }
  
  void SpinOneLed(int speed, CRGB color)  
  //make one led "spin" around the fan by lighting them sequentially
  //parameters: speed - milliseconds between frame advances | color: color to use when running the effect 
  {
    const int FRAMELIMIT = NUMLEDS;    //number of frames in this effect
    CheckInitialization();             //check to see if function has been given a start frame at first run and give one if necessary
    if (!CheckTimeForFrameDraw(speed)) //manage frame write timing
      return;
    BlankFan();                        //write black to all leds before writing frame data
    leds[frameNumber] = color;         //write color to led with same number as frame number    
    //WriteColorsToFan();                //write internal led array to external one for subsequent write to hardware at end of main loop
    FrameAdvance(speed, FRAMELIMIT);   //manage frame advancement
  }
};
#endif