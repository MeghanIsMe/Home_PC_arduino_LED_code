/*
  
*/

// include LED control library
#include "FastLED.h"
#include "functionsfordoggos.h"

// include this library's description file
#include "classesfordoggos.h"


//**********************************************************************************************************************
//**********************************************************************************************************************
//**************************************** GENERIC FAN CLASS************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************

//********************
//MANAGEMENT FUNCTIONS
//********************

///////////////////////////////////
// ADD ELAPSED TIME TO TOTAL
//Adds milliseconds since last main loop execution to running total
void generic_Fan::AddElapsedTimeToTotal(int deltaMillis)
{
	accumulatedMilliseconds += deltaMillis;
}

//called by effects function to see if the frame number is initialized and initialize it if necessary.
//new fan objects have a non-intialized frame number, so this sets it to 0.
//could also be used to switch to a different frame number before or while running, possibly. Not implemented yet.
void generic_Fan::CheckInitialization()
{
	if (!initialized)
	{
	  frameNumber = 0;
	  initialized = 1;
	}
}

///////////////////////////////////
// CHECK TIME FOR FRAME DRAW
//checks to see whether enough time has passed to advance to the next frame of the effects animation
bool generic_Fan::CheckTimeForFrameDraw(int speed)  
{
	if (speed < 0)                            //convert negative speed to positive for internal comparison.
		speed *= -1;
	//accumulatedMilliseconds += deltaMillis;   //add elapsed millis since last function call to running total.   
	if (accumulatedMilliseconds < speed)      //check whether enough time has passed to write the next frame.
		return false;                           //if not, return false.
	else    
	{
		accumulatedMilliseconds = 0;
		return true;                            //if so, return true.
  }
}
///////////////////////////////////
// FRAME ADVANCE
//called by effects function to manage frame advancement
void generic_Fan::FrameAdvance(int speed, int FRAMELIMIT)
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

//******************
// EFFECTS FUNCTIONS
//******************

///////////////////////////////////
// BLANK FAN
//write black (off) to all LEDs on the fan
//typically called prior to code that writes the current frame to the output array
void generic_Fan::BlankFan()
{
	for (int i = 0; i < NUMLEDS; i++)
	  leds[i] = CRGB::Black;
}  

///////////////////////////////////
// SPIN ONE LED
//make one led "spin" around the fan by lighting them sequentially
//parameters: speed - milliseconds between frame advances | color: color to use when running the effect 
void generic_Fan::SpinOneLed(int speed, CRGB color)  

{
	//  housekeeping portion
	const int FRAMELIMIT = NUMLEDS;    // number of frames in this effect
	CheckInitialization();             // check to see if function has been given a start frame at first run and give one if necessary
	if (!CheckTimeForFrameDraw(speed)) // manage frame write timing
		return;
		
	// color management portion
	savedColor = CheckForRandomColor(color, savedColor, FRAMELIMIT, frameNumber, speed);
		
	// actual effects portion
	BlankFan();                        // write black to all leds before writing frame data
	leds[frameNumber] = savedColor;    // write color to led with same number as frame number    
	
	// WriteColorsToFan();              // write internal led array to external one for subsequent write to hardware at end of main loop
	
	// housekeeping portion
	FrameAdvance(speed, FRAMELIMIT);   // manage frame advancement
}



  

  




 