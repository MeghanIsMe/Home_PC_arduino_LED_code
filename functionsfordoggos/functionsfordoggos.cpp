/*
  functionsfordoggos.h - library for functions related to LED control for Arduino
  relies on FastLED library and classesfordoggos library
*/
#ifndef functionsfordoggos.h
#define functionsfordoggos.h

#include "Arduino.h"
#include "FastLED.h"
#include "classesfordoggos.h"

///////////////////////
//====MakeRandomColor
//Parameters: none
//returns a random CRGB color
CRGB MakeRandomColor()
{
  int rval = random(256);
  int gval = random(256);
  int bval = random(256);
  return CRGB(rval,gval,bval);
}

///////////////////////
//====CheckForRandomColor
//FUNCTIONS CALLED - MakeRandomColor - no parameters
//PARAMETERS:
//  FROM ORIGINAL CALL TO EFFECTS FUNCTION IN MAIN LOOP
//  		color - color specified in the function will use to run (black for random)
//		  speed - time in milliseconds between frames
//	PROPERTY OF THE OBJECT ASSOCIATED WITH THE EFFECTS METHOD
//  		frameNumber - what frame of the animation the effect is currently displaying
//		  savedColor	- the color saved in the calling object to use in displaying effect
//	DEFINED IN THE EFFECTS FUNCTION CALLING CRFC	
//  		FRAMELIMIT - the number of frames in the animation

//  Runs at the start of effects functions that can accept a random color
//  If the color passed to the effects function is black AND the frame number is the last frame of the animation
//  	  ARC generates and returns a random color
//  On other frame numbers, or with other colors
//			ARC returns the color already saved in the calling object's properties

CRGB CheckForRandomColor(CRGB color, CRGB savedColor, int FRAMELIMIT, int frameNumber, int speed)
{
// if a color is passed to CFRC, write that color to state tracking array for effect and exit
  if (color != CRGB::Black)
    return color;
	
  //First condition: positive speed, color is black, starting frame - returns new random color
  if ( (speed >= 0) && (color == CRGB::Black) && (frameNumber == 0) ) //if this was called after FrameAdvance, this would be -1
    return MakeRandomColor();  
 
  //Second condition: negative speed, color is black, starting frame - returns new random color
  else if ( (speed < 0) && (color == CRGB::Black) && (frameNumber == FRAMELIMIT -1) ) //if this was called after FrameAdvance, this would be FRAMELIMIT
    return MakeRandomColor();
   
  //Third condition: anything else - returns the color already in the state tracking array, which will have been put there by this function previously
  else
    return savedColor;  
	
}



#endif