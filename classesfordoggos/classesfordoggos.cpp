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
// 				CHECKINITIALIZATION
///////////////////////////////////
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

//////////////////////////////////////
// 				CHECK TIME FOR FRAME DRAW
//////////////////////////////////////
//checks to see whether enough time has passed to advance to the next frame of the effects animation
bool generic_Fan::CheckTimeForFrameDraw(int speed)  
{
	accumulatedMilliseconds += deltaMillis;		// add elapsed milliseconds since last main loop to running total
	if (speed < 0)                            // convert negative speed to positive for internal comparison.
		speed *= -1;	
	if (accumulatedMilliseconds < speed)      // check whether enough time has passed to write the next frame.
		return false;                           // if not, return false
	else    
	{
		accumulatedMilliseconds = 0;						// reset running total of milliseconds to 0
		return true;                            // if so, return true.
  }
}
///////////////////////////////////
// 				FRAME ADVANCE
///////////////////////////////////
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
// 				BLANK FAN
///////////////////////////////////
//write black (off) to all LEDs on the fan
//typically called prior to code that writes the current frame to the output array
void generic_Fan::BlankFan()
{
	for (int i = 0; i < NUMLEDS; i++)
	  leds[i] = CRGB::Black;
}  

///////////////////////////////////
// 				SPINCOLORWAVE
///////////////////////////////////
//Lights each LED around an Aspect fan sequentially, leaves them on, and repeats with a new color
//non-selectable color: always random
void generic_Fan::SpinColorWave(int speed)
{
	const int FRAMELIMIT = NUMLEDS;
	
	CheckInitialization();             // check to see if function has been given a start frame at first run and give one if necessary
	if (!CheckTimeForFrameDraw(speed)) // manage frame write timing
		return;
	savedColor = CheckForRandomColor(CRGB::Black, savedColor, FRAMELIMIT, frameNumber, speed);  // generates random color at start frame
			//hard-coded to black to create a new random color each go-around
	leds[frameNumber] = savedColor; //	lighting led corresponding to current frame number
	
	FrameAdvance(speed, FRAMELIMIT);  //manage frame advancement
}

///////////////////////////////////
// 				SPINLEDS
///////////////////////////////////
// make up to three leds spin around the fan by lighting them sequentially
// parameters: speed - milliseconds between frame advances | color: color to use when running the effect 
// this effect does not support random colors
void generic_Fan::SpinLeds(int speed, CRGB color1, CRGB color2 = CRGB::Black, CRGB color3 = CRGB::Black)
{
	int numberOfLights = 1;
	
	// housekeeping portion
	const int FRAMELIMIT = NUMLEDS;		 // number of frames in this effect
	CheckInitialization();             // check to see if function has been given a start frame at first run and give one if necessary
	if (!CheckTimeForFrameDraw(speed)) // manage frame write timing
		return;
	
	// Limiting fans with only 4 LEDS to having two colors
  if (NUMLEDS == 4)
		color3 = CRGB::Black;

	// counting the number of lights to use in this effect	
	if (color2 != CRGB::Black)
    numberOfLights++;
  if (color3 != CRGB::Black)
    numberOfLights++;
	
	// actual effects portion
	BlankFan();                        // write black to all leds before writing frame data
	
	// For one/first light
	leds[frameNumber] = color1;    		 // write color to led with same number as frame number 
  // for two lights only	
	if (numberOfLights == 2)  
		leds[ ( (NUMLEDS + (NUMLEDS/numberOfLights) + frameNumber) % NUMLEDS) ] = color2; 
	// produces framenumber + 2 wrapping around from NUMLEDS -1 to 0
	// for three lights only
	if (numberOfLights == 3)     
  {
		leds[ ( (NUMLEDS + (NUMLEDS/numberOfLights) + frameNumber) % NUMLEDS) ] = color2; 
		// produces framenumber + 2 wrapping around from NUMLEDS -1 to 0
		leds[ ( (NUMLEDS + ( (2 * NUMLEDS/numberOfLights)) + frameNumber) % NUMLEDS)] = color3; 
		// produces framenumber + 4 wrapping around from NUMLEDS -1 to 0
  }  	
		
	// housekeeping portion
	FrameAdvance(speed, FRAMELIMIT);   // manage frame advancement		
}

///////////////////////////////////
// 				SPIN ONE LED
///////////////////////////////////
//make one led "spin" around the fan by lighting them sequentially
//parameters: speed - milliseconds between frame advances | color: color to use when running the effect 
//This kind of only exists to support random colors since SpinLeds does everything else this effect does
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

///////////////////////////////////
// 				MOVING LINE
///////////////////////////////////
//Causes a color to move across the fan from top to bottom (reversible)
// on Aspect fans, uses top two LEDs, then middle two, then bottom two
// on CPU fan, does top to bottom to top
//TO TO - update to allow line to move left/right on cpu fan, or other ways on Aspect fan
void generic_Fan::MovingLine(int speed, CRGB color)
{
	const int FRAMELIMIT = NUMLEDS - 2;  // set number of frames in the effect
	if (frameNumber > FRAMELIMIT)				 // if another effect left the frame number too high, reset to 0
		frameNumber = 0;
	
	if (!CheckTimeForFrameDraw(speed)) // manage frame write timing
		return;
	BlankFan();
	
	if (NUMLEDS == 4)
		if (frameNumber == 0)
		{
			leds[frameNumber] = color;
			leds[frameNumber + 1] = color;
		}
		else if (frameNumber == 1)
		{
			leds[frameNumber + 1] = color;
			leds[frameNumber + 2] = color;
		}
	
	if (NUMLEDS == 6)
		if (frameNumber == 0)
		{
			leds[3] = color;
			leds[4] = color;
		}
		else if ((frameNumber == 1) || (frameNumber == 3))
		{
			leds[2] = color;
			leds[5] = color;
		}
		else if (frameNumber == 2)
		{
			leds[1] = color;
			leds[0] = color;
		}
		
		FrameAdvance(speed, FRAMELIMIT);
}


//**********************************************************************************************************************
//**********************************************************************************************************************
//**************************************** CPU FAN CLASS****************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************
  





 