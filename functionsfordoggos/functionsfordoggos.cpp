/*
  functionsfordoggos.h - library for functions related to LED control for Arduino
  relies on FastLED library and classesfordoggos library
*/
#ifndef functionsfordoggos.h
#define functionsfordoggos.h

#include "Arduino.h"
#include "FastLED.h"
#include "classesfordoggos.h"

//******************
// UTILITY FUNCTIONS
//******************

///////////////////////
//==== SerialPrintColor
// Accepts a CRGB variable and prints its red, green, and blue values in a formatted way, then prints a newline
void SerialPrintColor(CRGB color)
{
  int r = color.red;
  int g = color.green;
  int b = color.blue;

  Serial.print(" RED-");
  Serial.print(r);
  Serial.print(" GRN-");
  Serial.print(g);
  Serial.print(" BLU-");
  Serial.println(b);
}

///////////////////////
//==== PrintColorArray
// Accepts a CRGB array and prints each color in it. Must manual hard-code the array length.
void PrintColorArray(CRGB *arr, int length)
{	
	for (int i = 0; i < length; i++)
	{
		Serial.print("Line#: ");
		Serial.print(i);
		Serial.print(" ");
		SerialPrintColor(arr[i]);
	}
}

///////////////////////
//==== GetLengthOfBlackTerminatedArray
// Accepts a CRGB array and returns the number of elements in it as an int
int GetLengthOfBlackTerminatedCRGBArray(CRGB *arr)
{
		int lengthCount = 0;
		CRGB color = CRGB::Blue; //doesn't matter what color as long as it's not black
		do
		{
			color = arr[lengthCount];
			if (color != CRGB::Black)
				lengthCount++;
		} while (color != CRGB::Black);
		
		return lengthCount;	
}

///////////////////////
//==== SerialPrintVars
// makes debugging via serial.print suck a bit less ass
// accepts up to 5 int vars, prints them on one line with | in between them, then prints a new line
void SerialPrintVars(int var0 = 0, int var1 = 0, int var2 = 0, int var3 = 0, int var4 = 0)
{
  Serial.print("| ");
  Serial.print(var0);  
  Serial.print(" | ");
  Serial.print(var1);
  Serial.print(" | ");
  Serial.print(var2);
  Serial.print(" | ");
  Serial.print(var3);
  Serial.print(" | ");
  Serial.print(var4);
  Serial.print(" | ");
  Serial.println();
}

//*****************************
// COLOR MANIPULATION FUNCTIONS
//*****************************

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
// if a color other than black is passed to CFRC, return that color
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