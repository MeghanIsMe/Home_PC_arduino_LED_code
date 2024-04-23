/* **********************************************************
	FILE: classesfordoggos.cpp
Contains definitions for functions and classes from ledcontrolfordoggos.cpp

	AUTHOR: Meghan Allen

	ASCII font for large comments: 		
https://www.asciiart.eu/text-to-ascii-art - pagga		
************************************************************/

#include "ledcontrolfordoggos.h" // include this source file's header

// ░░░░░░░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░█░█░░░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░█▀▀░░░░░░░░
// ░▄▄▄░▄▄▄░█░█░░█░░░█░░█░░░░█░░░█░░░█░░░░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░▀▀█░▄▄▄░▄▄▄
// ░░░░░░░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░░▀░░░░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░░░░░

// ░█▀▀░█▀▀░█▀▄░▀█▀░█▀█░█░░░░░█▀█░█▀▄░▀█▀░█▀█░▀█▀░░░█▀▀░█▀█░█░░░█▀█░█▀▄
// ░▀▀█░█▀▀░█▀▄░░█░░█▀█░█░░░░░█▀▀░█▀▄░░█░░█░█░░█░░░░█░░░█░█░█░░░█░█░█▀▄
// ░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░░░▀░░░▀░▀░▀▀▀░▀░▀░░▀░░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀
// Accepts a CRGB variable and prints its red, green, and blue values in a formatted way, then prints a newline
//		Parameters:  
// color - the CRGB variable whose values will be printed to screen via serial connection

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

// ░█▀█░█▀▄░▀█▀░█▀█░▀█▀░░░█▀▀░█▀█░█░░░█▀█░█▀▄░░░█▀█░█▀▄░█▀▄░█▀█░█░█
// ░█▀▀░█▀▄░░█░░█░█░░█░░░░█░░░█░█░█░░░█░█░█▀▄░░░█▀█░█▀▄░█▀▄░█▀█░░█░
// ░▀░░░▀░▀░▀▀▀░▀░▀░░▀░░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░░░▀░▀░▀░▀░▀░▀░▀░▀░░▀░
// Accepts a CRGB array and prints each color in it. Must pass the array length.
//		Parameters:  
// arr - an array of CRGB vars whose colors will be printed via serial connection
// length - the number of elements in the array arr

void PrintColorArray(CRGB* arr, int length)
{	
	for (int i = 0; i < length; i++)
	{
		Serial.print("Line#: ");
		Serial.print(i);
		Serial.print(" ");
		SerialPrintColor(arr[i]);
	}
}

// ░█▀▀░█▀▀░▀█▀░█░░░█▀▀░█▀█░█▀▀░▀█▀░█░█░█▀█░█▀▀░█▀▄░█░░░█▀█░█▀▀░█░█░▀█▀░█▀▀░█▀▄░█▄█░▀█▀░█▀█░█▀█░▀█▀░█▀▀░█▀▄░█▀█░█▀▄░█▀▄░█▀█░█░█
// ░█░█░█▀▀░░█░░█░░░█▀▀░█░█░█░█░░█░░█▀█░█░█░█▀▀░█▀▄░█░░░█▀█░█░░░█▀▄░░█░░█▀▀░█▀▄░█░█░░█░░█░█░█▀█░░█░░█▀▀░█░█░█▀█░█▀▄░█▀▄░█▀█░░█░
// ░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀░░▀░░▀░▀░▀▀▀░▀░░░▀▀░░▀▀▀░▀░▀░▀▀▀░▀░▀░░▀░░▀▀▀░▀░▀░▀░▀░▀▀▀░▀░▀░▀░▀░░▀░░▀▀▀░▀▀░░▀░▀░▀░▀░▀░▀░▀░▀░░▀░
// Accepts a CRGB array and returns the number of elements prior to the first black in it as an int
//		Parameters:  
// arr - the array whose length will be determined and returned
int GetLengthOfBlackTerminatedCRGBArray(const CRGB* arr)
{
		int lengthCount = 0;
		CRGB color;
		do
		{
			color = arr[lengthCount];
			if (color != CRGB::Black)
				lengthCount++;
		} while (color != CRGB::Black);
		
		return lengthCount;	
}

// ░░░░░░░░░█▀▀░█▀█░█░░░█▀█░█▀▄░░░█▄█░█▀█░█▀█░▀█▀░█▀█░█░█░█░░░█▀█░▀█▀░▀█▀░█▀█░█▀█░░░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░█▀▀░░░░░░░░
// ░▄▄▄░▄▄▄░█░░░█░█░█░░░█░█░█▀▄░░░█░█░█▀█░█░█░░█░░█▀▀░█░█░█░░░█▀█░░█░░░█░░█░█░█░█░░░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░▀▀█░▄▄▄░▄▄▄
// ░░░░░░░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░░░▀░▀░▀░▀░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░▀░▀░░▀░░▀▀▀░▀▀▀░▀░▀░░░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░░░░░

// ░█▄█░█▀█░█░█░█▀▀░░░█▀▄░█▀█░█▀█░█▀▄░█▀█░█▄█░░░█▀▀░█▀█░█░░░█▀█░█▀▄
// ░█░█░█▀█░█▀▄░█▀▀░░░█▀▄░█▀█░█░█░█░█░█░█░█░█░░░█░░░█░█░█░░░█░█░█▀▄
// ░▀░▀░▀░▀░▀░▀░▀▀▀░░░▀░▀░▀░▀░▀░▀░▀▀░░▀▀▀░▀░▀░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀
// returns a random CRGB color
//		Parameters: none
CRGB MakeRandomColor()
{
  int rval = random(256);
  int gval = random(256);
  int bval = random(256);
  return CRGB(rval,gval,bval);
}

		// ░█▀▀░█░░░░░░░█▀▀░█▀▀░█▀█░█▀▀░█▀▄░▀█▀░█▀▀░░░█░░░█▀▀░█▀▄░░░█▀▄░█▀▀░█░█░▀█▀░█▀▀░█▀▀
		// ░█░░░█░░░▄▄▄░█░█░█▀▀░█░█░█▀▀░█▀▄░░█░░█░░░░░█░░░█▀▀░█░█░░░█░█░█▀▀░▀▄▀░░█░░█░░░█▀▀
		// ░▀▀▀░▀▀▀░░░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░▀▀░░░░▀▀░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀


// ░░░░░░░░░█▄█░█▀█░█▀█░█▀█░█▀▀░█▀▀░█▄█░█▀▀░█▀█░▀█▀░░░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░█▀▀░░░░░░░░
// ░▄▄▄░▄▄▄░█░█░█▀█░█░█░█▀█░█░█░█▀▀░█░█░█▀▀░█░█░░█░░░░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░▀▀█░▄▄▄░▄▄▄
// ░░░░░░░░░▀░▀░▀░▀░▀░▀░▀░▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░░▀░░░░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░░░░░

// ░█▀▀░█░█░█▀▀░█▀▀░█░█░▀█▀░█▀█░▀█▀░▀█▀░▀█▀░█▀█░█░░░▀█▀░▀▀█░█▀█░▀█▀░▀█▀░█▀█░█▀█
// ░█░░░█▀█░█▀▀░█░░░█▀▄░░█░░█░█░░█░░░█░░░█░░█▀█░█░░░░█░░▄▀░░█▀█░░█░░░█░░█░█░█░█
// ░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░░▀░░▀▀▀░▀▀▀░▀░▀
// called by effects function to see if the frame number is initialized and initialize it if necessary.
// new fan objects have a non-intialized frame number, so this sets it to 0.
// could also be used to switch to a different frame number before or while running, possibly. Not implemented yet.
//		Parameters: none
void generic_LedDevice::CheckInitialization()
{
	if (!initializedFrame)
	{
	  frameNumber = 0;
	  initializedFrame = 1;
	}
	if (!initializedColor)
	{
		paletteColorIndex = 0;
		initializedColor = 1;
	}		
}
// ░█▀▀░█░█░█▀▀░█▀▀░█░█░░░▀█▀░▀█▀░█▄█░█▀▀░░░█▀▀░█▀█░█▀▄░░░█▀▀░█▀▄░█▀█░█▄█░█▀▀░░░█▀▄░█▀▄░█▀█░█░█
// ░█░░░█▀█░█▀▀░█░░░█▀▄░░░░█░░░█░░█░█░█▀▀░░░█▀▀░█░█░█▀▄░░░█▀▀░█▀▄░█▀█░█░█░█▀▀░░░█░█░█▀▄░█▀█░█▄█
// ░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀░▀░░░░▀░░▀▀▀░▀░▀░▀▀▀░░░▀░░░▀▀▀░▀░▀░░░▀░░░▀░▀░▀░▀░▀░▀░▀▀▀░░░▀▀░░▀░▀░▀░▀░▀░▀
// called by effects functions to check whether enough time has passed to advance
// to the next frame of the effects animation. Returns true if the frame should advance,
// false otherwise.
//		Parameters:  
// speed - milliseconds between frame advancement: passed from calling function
// length - the number of elements in the array arr
// counter - pointer to the calling object's current accumulated milliseconds variable
bool generic_LedDevice::CheckTimeForFrameDraw(int speed, int* counter)  
{	
	*counter += deltaMillis;	// add elapsed milliseconds since last main loop to running total
	
	if (speed < 0)				// convert negative speed to positive for internal comparison.
		speed *= -1;	
		
	if (*counter < speed)		// check whether enough time has passed to write the next frame.		
		return false;			// if not, return false	
	else    
	{		
		*counter = 0;			// reset running total of milliseconds to 0
		return true;			// if so, return true.
  }
};

// ░█▀▀░█▀█░█▀█░█░█░░░▀█▀░█▀█░░░█▀▀░█░█░▀█▀░█▀▀░█▀▄░█▀█░█▀█░█░░░░░█▀█░█▀▄░█▀▄░█▀█░█░█
// ░█░░░█░█░█▀▀░░█░░░░░█░░█░█░░░█▀▀░▄▀▄░░█░░█▀▀░█▀▄░█░█░█▀█░█░░░░░█▀█░█▀▄░█▀▄░█▀█░░█░
// ░▀▀▀░▀▀▀░▀░░░░▀░░░░░▀░░▀▀▀░░░▀▀▀░▀░▀░░▀░░▀▀▀░▀░▀░▀░▀░▀░▀░▀▀▀░░░▀░▀░▀░▀░▀░▀░▀░▀░░▀░
// For copying the calling object's array of CRGB data to one of the arrays defined in
// the main program and associated to hardware LEDs via FastLED's addLeds statement.
//		Parameters:  
// extArray - an array of CRGB vars to which the calling object's CRGB array will be copied
void generic_LedDevice::CopyToExternalArray(CRGB* extArray)
{
	for (int i = 0; i < NUMLEDS; i++)		
	{										
		extArray[i] = p_objectLedArray[i];  // reads array via the calling object's pointer
	}
};

// ░█▀█░█▀▄░█░█░█▀█░█▀█░█▀▀░█▀▀░░░█▀▀░█▀█░█░░░█▀█░█▀▄
// ░█▀█░█░█░▀▄▀░█▀█░█░█░█░░░█▀▀░░░█░░░█░█░█░░░█░█░█▀▄
// ░▀░▀░▀▀░░░▀░░▀░▀░▀░▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀
// Advance Color runs prior to FrameAdvance. Once per cycle of frames, it updates the color used in the effect to the next color
// in the passed array. If the passed array is black, this function creates random colors as appropriate to the frame number
void generic_LedDevice::AdvanceColor(const CRGB* palette, int FRAMELIMIT, int speed)
{		
	//for positive speed, trigger on frame FRAMELIMIT - 1. For negative speed, trigger on frame 0
	if ( ( (speed >= 0) && (*p_activeFrameCounter == FRAMELIMIT - 1) )  || ( (speed < 0) && (*p_activeFrameCounter == 0) ) )	
	{
		if (palette[0] == CRGB::Black)		
			savedColor = MakeRandomColor();	// creates a random color if passed array is black				
		else
		{
			savedColor = palette[paletteColorIndex];
			paletteColorIndex++;			// otherwise move to next color in palette array 
		}
	}				
	// loop color array back to start if it reaches the end
	if ( paletteColorIndex > GetLengthOfBlackTerminatedCRGBArray(palette) - 1 ) 
		paletteColorIndex = 0;
};

// ░█▀█░█▀▄░█░█░█▀█░█▀█░█▀▀░█▀▀░░░█▀▀░█▀▄░█▀█░█▄█░█▀▀
// ░█▀█░█░█░▀▄▀░█▀█░█░█░█░░░█▀▀░░░█▀▀░█▀▄░█▀█░█░█░█▀▀
// ░▀░▀░▀▀░░░▀░░▀░▀░▀░▀░▀▀▀░▀▀▀░░░▀░░░▀░▀░▀░▀░▀░▀░▀▀▀
// called by effects function to manage advancement of frame number
// runs at end of an effects function to advnace the frame number appropriate
void generic_LedDevice::AdvanceFrame(int speed, int FRAMELIMIT)
{	
if (*p_activeFrameCounter > FRAMELIMIT)		// if another effect left the frame number too high, reset to 0
		*p_activeFrameCounter = 0;			// no fix needed for low end of range because all effects will start at frame 0
											// and will never go below -1 in correctly written functions
	if (speed >= 0)  		// with positive speed, frames increment from 0 to FRAMELIMIT             			
	{    
	  *p_activeFrameCounter += 1;			
	  if (*p_activeFrameCounter == FRAMELIMIT)  // when frameNumber reaches FRAMELIMIT, it resets to 0 before next function iteration
		*p_activeFrameCounter = 0;
	}
	else					// with negative speed, frames decrement from FRAMELIMIT -1 to -1
	{
	  *p_activeFrameCounter -= 1;			
	  if (*p_activeFrameCounter == -1)
		*p_activeFrameCounter = FRAMELIMIT -1;	// when frameNumber reaches -1, reset to FRAMELIMIT -1 before next function iteration		
	}		
};


// ░█▀▄░█░░░█▀█░█▀█░█░█░█░░░█▀▀░█▀▄░█▀▀
// ░█▀▄░█░░░█▀█░█░█░█▀▄░█░░░█▀▀░█░█░▀▀█
// ░▀▀░░▀▀▀░▀░▀░▀░▀░▀░▀░▀▀▀░▀▀▀░▀▀░░▀▀▀
// sets all of calling objects LEDs to black (off)
// called at the beginning of many effects functions 
//		parameters:
// NUMLEDS - the number of LEDs on the calling object. Attribute of individual child classes
// and passed by the method that the calling object is using to call BlankLeds
void generic_LedDevice::BlankLeds(int NUMLEDS)
{
	for (int i = 0; i < NUMLEDS; i++)
		p_objectLedArray[i] = BLACK;
}

// ░█▀▄░█░░░▀█▀░█▀█░█░█░░░█░░░█▀▀░█▀▄░█▀▀
// ░█▀▄░█░░░░█░░█░█░█▀▄░░░█░░░█▀▀░█░█░▀▀█
// ░▀▀░░▀▀▀░▀▀▀░▀░▀░▀░▀░░░▀▀▀░▀▀▀░▀▀░░▀▀▀
// blink all LEDs the same color following passed palette
//		Parameters:  
// speed - time in milliseconds between frame
// palette - color palette used for effect
void generic_LedDevice::BlinkLeds(int speed, const CRGB* palette)
{
	const int FRAMELIMIT = 2;

	if (!CheckTimeForFrameDraw(speed, p_activeTimer)) // manage frame write timing
	return;	
	
	BlankLeds(NUMLEDS);				// set all LEDs to black before writing frame
	
	if (frameNumber == 0)	// On frame 0, set all LEDs on with saved color
		for (int i = 0; i < NUMLEDS; i++)		// once for each LED
			p_objectLedArray[i] = savedColor;			
	
	AdvanceColor(palette, FRAMELIMIT, speed);	//manage color progression
	AdvanceFrame(speed, FRAMELIMIT);			// manage frame advancement	
};

// ░█░░░▀█▀░█▀▀░█░█░▀█▀░█▀█░█░░░█░░░█░░░█▀▀░█▀▄░█▀▀
// ░█░░░░█░░█░█░█▀█░░█░░█▀█░█░░░█░░░█░░░█▀▀░█░█░▀▀█
// ░▀▀▀░▀▀▀░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀▀░░▀▀▀
/* Set all LEDS on calling device to the color passed to function
This will almost never be called directly from main: instead, it will be called
as a portion of another effects function. In that context, NUMLEDS can be passed
directly from the calling object's attributes
	Parameters:
NUMLEDS - The number of LEDs to be lit
color - The color to set the LEDs to */
void generic_LedDevice::LightAllLeds(int NUMLEDS, CRGB color)
{
	for (int i = 0; i < NUMLEDS; i++)
		p_objectLedArray[i] = color;
};


			// ░█▀▀░█░░░░░░░█▀▀░█▀▀░█▀█░█▀▀░█▀▄░▀█▀░█▀▀░░░█▀▀░█▀█░█▀█░░░█▀▀░█░░░█▀█░█▀▀░█▀▀
			// ░█░░░█░░░▄▄▄░█░█░█▀▀░█░█░█▀▀░█▀▄░░█░░█░░░░░█▀▀░█▀█░█░█░░░█░░░█░░░█▀█░▀▀█░▀▀█
			// ░▀▀▀░▀▀▀░░░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░░░▀░░░▀░▀░▀░▀░░░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀

// ░░░░░░░░░░░█▀▀░█▀▀░█▀▀░█▀▀░█▀▀░▀█▀░█▀▀░░░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░█▀▀░░░░░░░░
// ░▄▄▄░▄▄▄░░░█▀▀░█▀▀░█▀▀░█▀▀░█░░░░█░░▀▀█░░░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░▀▀█░▄▄▄░▄▄▄
// ░░░░░░░░░░░▀▀▀░▀░░░▀░░░▀▀▀░▀▀▀░░▀░░▀▀▀░░░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░░░░░

// ░█▀▀░█▀█░█▀▄░█▀▀░░░▀█▀░█░█░█▀▄░█▀█░█░█░█▀▀░█░█░░░█▀▀░█▀█░█░░░█▀█░█▀▄░█▀▀
// ░█▀▀░█▀█░█░█░█▀▀░░░░█░░█▀█░█▀▄░█░█░█░█░█░█░█▀█░░░█░░░█░█░█░░░█░█░█▀▄░▀▀█
// ░▀░░░▀░▀░▀▀░░▀▀▀░░░░▀░░▀░▀░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀
// fades all LEDs on fan from one color to the next through the passed CRGB palette array. 
//		Parameters:
// speed - time in milliseconds between frame
// palette - color palette used for effect
void generic_Fan::FadeThroughColors(int speed, const CRGB* palette)
{
	const int FRAMELIMIT = GetLengthOfBlackTerminatedCRGBArray(palette);  // each color in the palette array gets one frame
	
	bool nextFrame = 1;
	float change; 						// to track amount of blending to apply to colors based on elapsed millis between frames
	float changePerMilli = 255 / (float)speed; // how much change is applied per millisecond
	change = changePerMilli * *p_activeTimer;  // how much change/blending to apply this function iteration	
	if (changePerMilli < 0)  			// convert to positive change in case of negative speed
	changePerMilli *= -1;	
	
	CheckInitialization();             // check to see if function has been given a start frame at first run 
	if (!CheckTimeForFrameDraw(speed, p_activeTimer)) // manage frame write timing
		nextFrame = 0;	
	
	// blends color matching current frame number into next color on the palette array
	for (int i = 0; i < NUMLEDS; i++)  
			p_objectLedArray[i] = blend(	 
				palette[*p_activeFrameCounter],		// argument 1																										 // argument 1
				(palette[ (*p_activeFrameCounter + 1) % GetLengthOfBlackTerminatedCRGBArray(palette) ]),  // argument 2
				change);							// argument 3														  					  			       			   // argument 3	
	
	if (nextFrame)
    AdvanceFrame(speed, FRAMELIMIT);  //advance frame as appropriate		
};

// ░█▀▀░█▀█░▀█▀░█▀█░░░█▀▀░█▀█░█░░░█▀█░█▀▄░░░█░█░█▀█░█░█░█▀▀
// ░▀▀█░█▀▀░░█░░█░█░░░█░░░█░█░█░░░█░█░█▀▄░░░█▄█░█▀█░▀▄▀░█▀▀
// ░▀▀▀░▀░░░▀▀▀░▀░▀░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░░░▀░▀░▀░▀░░▀░░▀▀▀
//Lights each LED around an Aspect fan sequentially, leaves them on, and repeats with a new color
//		Parameters:
// speed - time in milliseconds between frame
// palette - color palette used for effect
void generic_Fan::SpinColorWave(int speed, const CRGB* palette)

{
	const int FRAMELIMIT = NUMLEDS;

	CheckInitialization();             // check to see if function has been given a start frame at first run 
	if (!CheckTimeForFrameDraw(speed, p_activeTimer))	// manage frame write timing
		return;		

	p_objectLedArray[frameNumber] = savedColor;			// lighting led corresponding to current frame number
	//SerialPrintColor(leds[frameNumber]);
	
	AdvanceColor(palette, FRAMELIMIT, speed);			// manage color progression	
	AdvanceFrame(speed, FRAMELIMIT);  				  	// manage frame advancement	
};

// ░█▀▀░█▀█░▀█▀░█▀█░░░█▀▀░█▀█░█░░░█▀█░█▀▄░░░█░█░█▀█░█░█░█▀▀░░░█▀▀░█▀█░█▀▄░█▀▀
// ░▀▀█░█▀▀░░█░░█░█░░░█░░░█░█░█░░░█░█░█▀▄░░░█▄█░█▀█░▀▄▀░█▀▀░░░█▀▀░█▀█░█░█░█▀▀
// ░▀▀▀░▀░░░▀▀▀░▀░▀░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░░░▀░▀░▀░▀░░▀░░▀▀▀░░░▀░░░▀░▀░▀▀░░▀▀▀
// Rotates a light around a fan while leaving a trail that fades behind it
//		Parameters:
// speed - time in milliseconds between frame
// palette - color palette used for effect
// fadeAmount - factor by which to multiply each led value at each frame until rewritten with new frame
void generic_Fan::SpinColorWaveFade(int speed, const CRGB* palette, float fadeAmount /* 0.3 */)
{
	const int FRAMELIMIT = NUMLEDS;
	if (!CheckTimeForFrameDraw(speed, p_activeTimer))	// manage frame write timing
		return;		
		
	for (int i = 0; i < NUMLEDS; i++)	// fade each LED by a percentage passed to function (40% default)
	{
		p_objectLedArray[i].red *= fadeAmount;
		p_objectLedArray[i].green *= fadeAmount;
		p_objectLedArray[i].blue *= fadeAmount;
	}
	p_objectLedArray[*p_activeFrameCounter] = savedColor;	// light LED matching frame number
		
	AdvanceColor(palette, FRAMELIMIT, speed);		// manage color progression	
	AdvanceFrame(speed, FRAMELIMIT);				// manage frame advancement
};
	
// ░█▀▀░█▀█░▀█▀░█▀█░░░█░░░█▀▀░█▀▄░█▀▀
// ░▀▀█░█▀▀░░█░░█░█░░░█░░░█▀▀░█░█░▀▀█
// ░▀▀▀░▀░░░▀▀▀░▀░▀░░░▀▀▀░▀▀▀░▀▀░░▀▀▀
// make up to three leds spin around the fan by lighting them sequentially
// parameters: speed - milliseconds between frame advances | color: color to use when running the effect 
// this effect does not support random colors
//		Parameters:
// speed - time in milliseconds between frame
// CRGB vars - the respective colors of the lights to spin around the fan
void generic_Fan::SpinLeds(int speed, CRGB color1, CRGB color2 , CRGB color3)
{
	int numberOfLights = 1;
	
	// housekeeping portion
	const int FRAMELIMIT = NUMLEDS;		 // number of frames in this effect
	CheckInitialization();             // check to see if function has been given a start frame at first run and give one if necessary
	if (!CheckTimeForFrameDraw(speed, p_activeTimer)) // manage frame write timing
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
	BlankLeds(NUMLEDS);	// write black to all leds before writing frame data	

	// For one/first light
	p_objectLedArray[frameNumber] = color1;	// write color to led with same number as frame number 
  	
	// for two lights only	
	if (numberOfLights == 2)  
		p_objectLedArray[ ( (NUMLEDS + (NUMLEDS/numberOfLights) + frameNumber) % NUMLEDS) ] = color2; 
	// produces framenumber + 2 wrapping around from NUMLEDS -1 to 0 - no it doesn't- comment needs rewriting
	
	// for three lights only
	if (numberOfLights == 3)     
	{
		p_objectLedArray[ ( (NUMLEDS + (NUMLEDS/numberOfLights) + frameNumber) % NUMLEDS) ] = color2; 
		// produces framenumber + 2 wrapping around from NUMLEDS -1 to 0
		p_objectLedArray[ ( (NUMLEDS + ( (2 * NUMLEDS/numberOfLights)) + frameNumber) % NUMLEDS)] = color3; 
		// produces framenumber + 4 wrapping around from NUMLEDS -1 to 0
	}  		
		
	// housekeeping portion
	AdvanceFrame(speed, FRAMELIMIT);   // manage frame advancement		
}

// ░█▀▀░█▀█░▀█▀░█▀█░░░█▀█░█▀█░█▀▀░░░█░░░█▀▀░█▀▄
// ░▀▀█░█▀▀░░█░░█░█░░░█░█░█░█░█▀▀░░░█░░░█▀▀░█░█
// ░▀▀▀░▀░░░▀▀▀░▀░▀░░░▀▀▀░▀░▀░▀▀▀░░░▀▀▀░▀▀▀░▀▀░
// make one led "spin" around the fan by lighting them sequentially
// This supports color cycling through paelettes, whereas SpinLeds does not
//		Parameters:
// speed - time in milliseconds between frame
// palette - color palette used for effect
void generic_Fan::SpinOneLed(int speed, const CRGB* palette)  
{
	//  housekeeping portion
	const int FRAMELIMIT = NUMLEDS;    // number of frames in this effect
	
	CheckInitialization();             // check to see if function has been given a start frame at first run and give one if necessary
	if (!CheckTimeForFrameDraw(speed, p_activeTimer)) // manage frame write timing
		return;		
		
	// actual effects portion
	BlankLeds(NUMLEDS);                        // write black to all leds before writing frame data
	p_objectLedArray[frameNumber] = savedColor;    // write color to led with same number as frame number    
	
	// housekeeping portion
	AdvanceColor(palette, FRAMELIMIT, speed);
	AdvanceFrame(speed, FRAMELIMIT);   // manage frame advancement
}

// ░█▄█░█▀█░█░█░▀█▀░█▀█░█▀▀░░░█░░░▀█▀░█▀█░█▀▀
// ░█░█░█░█░▀▄▀░░█░░█░█░█░█░░░█░░░░█░░█░█░█▀▀
// ░▀░▀░▀▀▀░░▀░░▀▀▀░▀░▀░▀▀▀░░░▀▀▀░▀▀▀░▀░▀░▀▀▀
//Causes a color to move across the fan from top to bottom (reversible)
// on Aspect fans, uses top two LEDs, then middle two, then bottom two
// on CPU fan, does top to bottom to top
//		Parameters:
// speed - time in milliseconds between frame
// palette - color palette used for effect
//		TO DO - update to allow line to move left/right on cpu fan, or other ways on Aspect fan
// Can this be written separately for Aspect vs CPU classes to avoid the outer if/else structure?
void generic_Fan::MovingLine(int speed, const CRGB* palette)
{
	const int FRAMELIMIT = NUMLEDS - 2;  													// set number of frames in the effect
		
	if (!CheckTimeForFrameDraw(speed, p_activeTimer))	// manage frame write timing
		return;
		
	BlankLeds(NUMLEDS);
	
	if (NUMLEDS == 4)
	{
		if (frameNumber == 0)
		{
			p_objectLedArray[frameNumber] = savedColor;
			p_objectLedArray[frameNumber + 1] = savedColor;
		}
		else if (frameNumber == 1)
		{
			p_objectLedArray[frameNumber + 1] = savedColor;
			p_objectLedArray[frameNumber + 2] = savedColor;
		}
	}
	
	if (NUMLEDS == 6)
	{
		if (frameNumber == 0)
		{
			p_objectLedArray[3] = savedColor;
			p_objectLedArray[4] = savedColor;
		}
		else if ((frameNumber == 1) || (frameNumber == 3))
		{
			p_objectLedArray[2] = savedColor;
			p_objectLedArray[5] = savedColor;
		}
		else if (frameNumber == 2)
		{
			p_objectLedArray[1] = savedColor;
			p_objectLedArray[0] = savedColor;
		}
	}
		
		AdvanceColor(palette, FRAMELIMIT, speed);
		AdvanceFrame(speed, FRAMELIMIT);
};

			// ░█▀▀░█░░░░░░░█▀█░█▀▀░█▀█░█▀▀░█▀▀░▀█▀░░░█▀▀░█▀█░█▀█
			// ░█░░░█░░░▄▄▄░█▀█░▀▀█░█▀▀░█▀▀░█░░░░█░░░░█▀▀░█▀█░█░█
			// ░▀▀▀░▀▀▀░░░░░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░░▀░░░░▀░░░▀░▀░▀░▀

			// ░█▀▀░█░░░░░░░█▀▄░█░█░█▀█░█░░░░░█▀▀░█▀▄░█▀█░█▀█░▀█▀░░░█▀█░█▀▀░█▀█░█▀▀░█▀▀░▀█▀░░░█▀▀░█▀█░█▀█░█▀▀
			// ░█░░░█░░░▄▄▄░█░█░█░█░█▀█░█░░░░░█▀▀░█▀▄░█░█░█░█░░█░░░░█▀█░▀▀█░█▀▀░█▀▀░█░░░░█░░░░█▀▀░█▀█░█░█░▀▀█
			// ░▀▀▀░▀▀▀░░░░░▀▀░░▀▀▀░▀░▀░▀▀▀░░░▀░░░▀░▀░▀▀▀░▀░▀░░▀░░░░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░░▀░░░░▀░░░▀░▀░▀░▀░▀▀▀

// ░░░░░░░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░█░█░░░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░█▀▀░░░░░░░░
// ░▄▄▄░▄▄▄░█░█░░█░░░█░░█░░░░█░░░█░░░█░░░░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░▀▀█░▄▄▄░▄▄▄
// ░░░░░░░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░░▀░░░░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░░░░░

// ░▀█▀░█▀▄░█▀█░█▀█░█▀▀░█░░░█▀█░▀█▀░█▀▀░░░█░░░█▀▀░█▀▄░█▀▀░░░▀█▀░█▀█░░░█▀█░█░█░▀█▀░█▀█░█░█░▀█▀░░░█▀█░█▀▄░█▀▄░█▀█░█░█
// ░░█░░█▀▄░█▀█░█░█░▀▀█░█░░░█▀█░░█░░█▀▀░░░█░░░█▀▀░█░█░▀▀█░░░░█░░█░█░░░█░█░█░█░░█░░█▀▀░█░█░░█░░░░█▀█░█▀▄░█▀▄░█▀█░░█░
// ░░▀░░▀░▀░▀░▀░▀░▀░▀▀▀░▀▀▀░▀░▀░░▀░░▀▀▀░░░▀▀▀░▀▀▀░▀▀░░▀▀▀░░░░▀░░▀▀▀░░░▀▀▀░▀▀▀░░▀░░▀░░░▀▀▀░░▀░░░░▀░▀░▀░▀░▀░▀░▀░▀░░▀░
// Copies the colors stored in the objects 1 dimenaional leds array to the 
// appropriate elements of the 2 dimensional dualFans array in preparation 
// for the dualFans array being written to the output array in the main loop

void dual_FrontAspectFans::CopyToTwoExternalArrays(CRGB* fan1 /* top */, CRGB* fan0 /* bottom */)
{
	fan1[1] = p_objectLedArray[0];
	fan1[2] = p_objectLedArray[1];
	fan1[3] = p_objectLedArray[2];
	fan0[1] = p_objectLedArray[3];
	fan0[2] = p_objectLedArray[4];
	fan0[3] = p_objectLedArray[5];

	fan1[0] = p_objectLedArray[6];
	fan1[5] = p_objectLedArray[7];
	fan1[4] = p_objectLedArray[8];
	fan0[0] = p_objectLedArray[9];
	fan0[5] = p_objectLedArray[10];
	fan0[4] = p_objectLedArray[11];
}

// order of leds array on the fans as defined above is:
// LEFT |  RIGHT | OUTPUT
//  0		6		[1][1], [1][0]
//  1		7		[1][2], [1][5]
//  2		8		[1][3], [1][4]
//  3		9		[0][1], [0][0]
//  4		10		[0][2], [0][5]
//  5		11		[0][3], [0][4]


// ░█▀▀░▀█▀░█▀█░█▀▄░░░█░█░▀█▀░█▀▀░█░█░█▀▀░█▀▀░▀█▀░░░█░░░▀█▀░█▀▄░░░█░░░█▀▀░█▀▄
// ░█▀▀░░█░░█░█░█░█░░░█▀█░░█░░█░█░█▀█░█▀▀░▀▀█░░█░░░░█░░░░█░░█░█░░░█░░░█▀▀░█░█
// ░▀░░░▀▀▀░▀░▀░▀▀░░░░▀░▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░░▀░░░░▀▀▀░▀▀▀░▀▀░░░░▀▀▀░▀▀▀░▀▀░
// checks one side of the front fans to find the highest up LED that is not set to black
// boolean side deterines which side of the front fans to check
int dual_FrontAspectFans::FindHighestLitLed(bool side)
{	
	if (side == 0) // left side
	{
		if (leds[5] != CRGB::Black)
			return 5;
		else if (leds[4] != CRGB::Black)
			return 4;
		else if (leds[3] != CRGB::Black)
			return 3;
		else if (leds[2] != CRGB::Black)
			return 2;
		else if (leds[1] != CRGB::Black)
			return 1;
		else if (leds[0] != CRGB::Black)
			return 0;
	}
	else // right side
	{
		if (leds[11] != CRGB::Black)
			return 11;
		else if (leds[10] != CRGB::Black)
			return 10;
		else if (leds[9] != CRGB::Black)
			return 9;
		else if (leds[8] != CRGB::Black)
			return 8;
		else if (leds[7] != CRGB::Black)
			return 7;
		else if (leds[6] != CRGB::Black)
			return 6;
	}
	return -1;  // added to get ride of compiler warning
}



// ░░░░░░░░░█▀▀░█▀▀░█▀▀░█▀▀░█▀▀░▀█▀░█▀▀░░░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░█▀▀░░░░░░░░
// ░▄▄▄░▄▄▄░█▀▀░█▀▀░█▀▀░█▀▀░█░░░░█░░▀▀█░░░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░▀▀█░▄▄▄░▄▄▄
// ░░░░░░░░░▀▀▀░▀░░░▀░░░▀▀▀░▀▀▀░░▀░░▀▀▀░░░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░░░░░


// ░█▄█░█▀█░█░█░▀█▀░█▀█░█▀▀░█░░░▀█▀░█▀█░█▀▀░█▀▄░█░█░█▀█░█░░░█▀█░█▀▀░█▀█░█▀▀░█▀▀░▀█▀
// ░█░█░█░█░▀▄▀░░█░░█░█░█░█░█░░░░█░░█░█░█▀▀░█░█░█░█░█▀█░█░░░█▀█░▀▀█░█▀▀░█▀▀░█░░░░█░
// ░▀░▀░▀▀▀░░▀░░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀░░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░░▀░
void dual_FrontAspectFans::MovingLineDualAspect(int speed, const CRGB* palette)
{
	const int FRAMELIMIT = 6;  													// set number of frames in the effect
		
	if (!CheckTimeForFrameDraw(speed, p_activeTimer))	// manage frame write timing
		return;

	BlankLeds(NUMLEDS);
	/*
	for (int i = 0; i < NUMLEDS; i++ )
		p_objectLedArray[i] = CRGB::Black;
	*/

	if (*p_activeFrameCounter == 0)
	{
		p_objectLedArray[0] = savedColor;
		p_objectLedArray[6] = savedColor;
	}
	else if (*p_activeFrameCounter == 1)
	{
		p_objectLedArray[1] = savedColor;
		p_objectLedArray[7] = savedColor;
	}
		else if (*p_activeFrameCounter == 2)
	{
		p_objectLedArray[2] = savedColor;
		p_objectLedArray[8] = savedColor;
	}
		else if (*p_activeFrameCounter == 3)
	{
		p_objectLedArray[3] = savedColor;
		p_objectLedArray[9] = savedColor;
	}
		else if (*p_activeFrameCounter == 4)
	{
		p_objectLedArray[4] = savedColor;
		p_objectLedArray[10] = savedColor;
	}
		else if (*p_activeFrameCounter == 5)
	{
		p_objectLedArray[5] = savedColor;
		p_objectLedArray[11] = savedColor;
	}
	
	AdvanceColor(palette, FRAMELIMIT, speed);
	AdvanceFrame(speed, FRAMELIMIT);
};

// ░█▀▀░▀█▀░█▀█░█▀▀░█░█░░░█▀▀░▀█▀░█░░░█░░
// ░▀▀█░░█░░█▀█░█░░░█▀▄░░░█▀▀░░█░░█░░░█░░
// ░▀▀▀░░▀░░▀░▀░▀▀▀░▀░▀░░░▀░░░▀▀▀░▀▀▀░▀▀▀
// LEDs fill up from bottom to top of the two front fans, progressing through colors in the palette
// currently not reversible
void dual_FrontAspectFans::StackFill(int speed, const CRGB* palette)
{
	const int FRAMELIMIT = 12;
	
	if (!CheckTimeForFrameDraw(speed, &accumulatedMilliseconds))	// manage frame write timing
		return;
	
	if (activeSide == 0)
		StackLeft();
	else
		StackRight();	
	
	activeSide = !activeSide;
		
	AdvanceColor(palette, FRAMELIMIT, speed);
	AdvanceFrame(speed, FRAMELIMIT);
};

void dual_FrontAspectFans::StackLeft()
{
	leds[leftCount] = savedColor;
	leftCount++;
	if (leftCount > 5)
		leftCount = 0;
};

void dual_FrontAspectFans::StackRight()
{
	if (rightCount == 0)
		rightCount = 6;
	
	leds[rightCount] = savedColor;
	rightCount++;
	if (rightCount > 11)
		leftCount = 6;
};

// STACKLEFT - SUB-FUNCTION FOR STACKFILL
/*
void dual_FrontAspectFans::StackLeft()
{
	int ledOrder[] = {3,2,1};
	if (leftCount <  3)
	{		
		dualFans[0][ ledOrder[leftCount] ] = savedColor;
	}		
	else
	{		
		dualFans[1][ ledOrder[leftCount % 3] ] = savedColor;
	}
	
	leftCount++;
	if (leftCount > 5)
		leftCount = 0;
};
*/

// STACKRIGHT - SUB-FUNCTION FOR STACKFILL
/*
void dual_FrontAspectFans::StackRight()
{
	int ledOrder[] = {4,5,0};
	if (rightCount < 3)
		dualFans[0][ ledOrder[rightCount] ] = savedColor;
	else
		dualFans[1][ ledOrder[rightCount % 3] ] = savedColor;
	
	rightCount++;
	if (rightCount > 5)
		rightCount = 0;
};
*/

			// ░█▀▀░█░░░░░░░█▀▀░█▀▄░█▀█░█▀█░▀█▀░░░█░░░█▀▀░█▀▄░░░█▀▀░▀█▀░█▀▄░▀█▀░█▀█
			// ░█░░░█░░░▄▄▄░█▀▀░█▀▄░█░█░█░█░░█░░░░█░░░█▀▀░█░█░░░▀▀█░░█░░█▀▄░░█░░█▀▀
			// ░▀▀▀░▀▀▀░░░░░▀░░░▀░▀░▀▀▀░▀░▀░░▀░░░░▀▀▀░▀▀▀░▀▀░░░░▀▀▀░░▀░░▀░▀░▀▀▀░▀░░

// ░░░░░░░░░█░█░▀█▀░▀█▀░█░░░▀█▀░▀█▀░█░█░░░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░█▀▀░░░░░░░░
// ░▄▄▄░▄▄▄░█░█░░█░░░█░░█░░░░█░░░█░░░█░░░░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░▀▀█░▄▄▄░▄▄▄
// ░░░░░░░░░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀░░▀░░░▀░░░░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░░░░░

// ░█▀▄░█▀▀░▀█▀░█▀▀░█▀▄░█▄█░▀█▀░█▀█░█▀▀░░░▀█▀░▀█▀░█▄█░█▀▀░█▀▄
// ░█░█░█▀▀░░█░░█▀▀░█▀▄░█░█░░█░░█░█░█▀▀░░░░█░░░█░░█░█░█▀▀░█▀▄
// ░▀▀░░▀▀▀░░▀░░▀▀▀░▀░▀░▀░▀░▀▀▀░▀░▀░▀▀▀░░░░▀░░▀▀▀░▀░▀░▀▀▀░▀░▀
// Determines which frame counting member to use for function timing based on which quarters of the strip are engaged
// In order of priority, assigns the first timer that matches a booleans: tl, tr, bl, br
// Parameters:
// bool vars - one for each quarter of the strip to indicate whether or not
// 		calling effect is running on it
void front_LedStrip::DetermineTimer(bool tl, bool tr, bool bl, bool br)
{	
	if (tl)	
	{
		p_activeFrameCounter = &topLeftFrameNumber;
		p_activeTimer =  &topLeftAccumulatedMillis;	
	}
	else if (tr)	
	{
		p_activeFrameCounter = &topRightFrameNumber;	
		p_activeTimer = &topRightAccumulatedMillis;
	}
	else if (bl)	
	{
		p_activeFrameCounter = &bottomLeftFrameNumber;
		p_activeTimer =  &bottomLeftAccumulatedMillis;
	}
	else if (br)	
	{
		p_activeFrameCounter = &bottomRightFrameNumber;	
		p_activeTimer =  &bottomRightAccumulatedMillis;
	}
}

// ░░░░░░░░░█▀▀░█▀▀░█▀▀░█▀▀░█▀▀░▀█▀░█▀▀░░░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░█▀▀░░░░░░░░
// ░▄▄▄░▄▄▄░█▀▀░█▀▀░█▀▀░█▀▀░█░░░░█░░▀▀█░░░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░▀▀█░▄▄▄░▄▄▄
// ░░░░░░░░░▀▀▀░▀░░░▀░░░▀▀▀░▀▀▀░░▀░░▀▀▀░░░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░░░░░

// ░█▀▀░█░█░█▀█░█▀▀░█▀▀░░░█░█░▀█▀░▀█▀░█░█░░░█▀▀░█▀█░█▀▄░█▀▀
// ░█░░░█▀█░█▀█░▀▀█░█▀▀░░░█▄█░░█░░░█░░█▀█░░░█▀▀░█▀█░█░█░█▀▀
// ░▀▀▀░▀░▀░▀░▀░▀▀▀░▀▀▀░░░▀░▀░▀▀▀░░▀░░▀░▀░░░▀░░░▀░▀░▀▀░░▀▀▀
//		Parameters:
// speed - time in milliseconds between frame
// palette - color palette used for effect
// fadeAmount - factor by which to multiply each LED at frameAdvance
// lights * 1 * - the number of LEDs to use in the chasing effect
void front_LedStrip::ChaseWithFade(int speed, const CRGB* palette, float fadeAmount, int lights /* 1 */)
{
	const int FRAMELIMIT = NUMLEDS;
	if (!CheckTimeForFrameDraw(speed, p_activeTimer)) // manage frame write timing
		return;		
		
	// first, fade all the LEDs by selected amount
	for (int i = 0; i < NUMLEDS; i++)  
	{
		p_objectLedArray[i].red *= fadeAmount;
		p_objectLedArray[i].green *= fadeAmount;
		p_objectLedArray[i].blue *= fadeAmount;
	}
	// second, light led by framenumber
	p_objectLedArray[*p_activeFrameCounter] = savedColor;   // for one light	
	if (lights == 2)										// for two lights	
		p_objectLedArray[(*p_activeFrameCounter + 10) % 20] = savedColor;	
		
	AdvanceColor(palette, FRAMELIMIT, speed);	// manage color progression	
	AdvanceFrame(speed, FRAMELIMIT);			// manage frame advancement
};

// ░█▀▀░█▀▀░█▀▄░█▀█░█░░░█░░░░░█▀▀░█▀█░█░░░█▀█░█▀▄░█▀▀
// ░▀▀█░█░░░█▀▄░█░█░█░░░█░░░░░█░░░█░█░█░░░█░█░█▀▄░▀▀█
// ░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀
//  Scrolls a set of colors passed in via an array on one or more quarters of the front LED strips
//  This is called by ScrollColorsOnFrontStrips (SCOFS)
//		SCOFS determines the number of vertical rows and passes the booleans determining which parts of the strips to run on
//	Accepts an array of colors to use
//	Creates an array of double that length (baseArray) which includes blends of colors between the ones on the input array
//	Does math to write baseArray's values into outArray in the correct order based on frame number
//	Calls WriteColorsToOutPutArray to write outArray to the calling object's LED array
//		Parameters:
// speed - time in milliseconds between advancing a color fully from one array position to the next (one frame)
// palette - color palette used for effect
// vertRows - the number of vertical LEDs the effect spans - either 5 or 10
//	determined by ScrollColorsOnFrontStrips function and passed to ScrollColors
// bool vars - one for each quarter of the strip to indicate whether or not
//	calling effect is running on it
void front_LedStrip::ScrollColors(int speed, const CRGB* palette, int vertRows, bool tl, bool tr, bool bl, bool br)
{
	int lengthOfInputArray = (GetLengthOfBlackTerminatedCRGBArray(palette)); // the number of colors in the passed array
	int lengthOfBaseArray = lengthOfInputArray * 2;		// the base array holds the input array plus blends	
	int count = 1; 								// math for assigning blended colors to baseArray
	const int FRAMELIMIT = lengthOfBaseArray; 	// how many frames until positions of input array colors repeat
	float change; 								// to track amount of blending to apply to colors based on elapsed millis between frames
	float changePerMilli = 255 / (float)speed;	// how much change is applied per millisecond
	bool nextFrame = 1; 		 				// flag to advance frame at end of function
	CRGB baseArray[lengthOfBaseArray];  		// array to hold basecolors and blended colors
  	CRGB outArray[vertRows];					// Array to hold colors ready to write out to LEDs
	CRGB blendColor;							// to temporarily hold color to write to outarray	
	
	DetermineTimer(tl, tr, bl, br);  			// determine which of the object's frame counters and timers to run the effect on		
												// this sets the pointers p_activeFrameCounter and p_activeTimer
	
	if (!CheckTimeForFrameDraw(speed, p_activeTimer))	// manage frame write - if false, function progresses with between-frame blending
			nextFrame = 0;								// but will not advance frame	
			
	if (changePerMilli < 0)  					// convert to positive change in case of negative speed
		changePerMilli *= -1;	
	
	change = changePerMilli * *p_activeTimer;  	// how much change/blending to apply this function iteration	
					
	// populating base array
	for (int i = 0; i < lengthOfBaseArray; i++) // once for each color + each color blend
	{		
		if (i % 2 == 0)			// even lines (and 0) get colors directly from input array
			baseArray[i] = palette[ (i / 2) % lengthOfInputArray];
		else if (i % 2 == 1)	// odd lines get blends of colors from input array
		{	
			baseArray[i] = blend( palette[ (i - count) % lengthOfInputArray], palette[ (i - count + 1) % lengthOfInputArray], 128);
			count++;			
		}		
	}	
	
	// Populate outArray with blends of the colors in the base array
  	// for positive speed
	if (speed >= 0)
		for (int i = 0; i < vertRows; i++)  //once for each hardware row
			{							
				outArray[i] = blend(
					(baseArray[ (i + *p_activeFrameCounter) % lengthOfBaseArray ]),		// argument 1
					(baseArray[ (i + 1 + *p_activeFrameCounter) % lengthOfBaseArray ]),	// argument 2
					change);															// argument 3																				  			          // argument 3
			}     
	// for negative speed
	else if (speed < 0)  
		for (int i = 0; i < vertRows; i++)
		{				
			outArray[i] = blend(										 
				(baseArray [(*p_activeFrameCounter + i) % lengthOfBaseArray ]),								// argument 1
				(baseArray [ (*p_activeFrameCounter - 1 + lengthOfBaseArray + i) % lengthOfBaseArray ] ),   // argument 2
				change);																					// argument 3																								 								 							     // argument 3				
		}		
	//populate object's array of LEDs with the colors to be written to the hardware		
	WriteColorsToOutPutArray(outArray, tl, tr, bl, br, vertRows);	  
	
	if (nextFrame)
    	AdvanceFrame(speed, FRAMELIMIT);  //advance frame as appropriate		
}

// ░█▀▀░█▀▀░█▀▄░█▀█░█░░░█░░░░░█▀▀░█▀█░█░░░█▀█░█▀▄░█▀▀░░░█▀█░█▀█░░░█▀▀░█▀▄░█▀█░█▀█░▀█▀░░░█▀▀░▀█▀░█▀▄░▀█▀░█▀█░█▀▀
// ░▀▀█░█░░░█▀▄░█░█░█░░░█░░░░░█░░░█░█░█░░░█░█░█▀▄░▀▀█░░░█░█░█░█░░░█▀▀░█▀▄░█░█░█░█░░█░░░░▀▀█░░█░░█▀▄░░█░░█▀▀░▀▀█
// ░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░▀▀▀░▀░▀░░░▀░░░▀░▀░▀▀▀░▀░▀░░▀░░░░▀▀▀░░▀░░▀░▀░▀▀▀░▀░░░▀▀▀
//  Calls ScrollColors and provides the booleans passed to this argument plus the number of vertical rows determined in this function
void front_LedStrip::ScrollColorsOnFrontStrips(int speed, const CRGB* palette, bool tl, bool tr, bool bl, bool br)
{
	int vertRows;	
	if ( ( (tl) || (tr) ) && ( (bl) || (br) ) )  // if at least one upper and one lower strip are engaged, 10 rows. Else, 5.
		vertRows = 10;
	else
		vertRows = 5;	
	
	front_LedStrip::ScrollColors(speed, palette, vertRows, tl, tr, bl, br);	
}

// ░█░█░█▀▄░▀█▀░▀█▀░█▀▀░░░█▀▀░█▀█░█░░░█▀█░█▀▄░█▀▀░░░▀█▀░█▀█░░░█▀█░█░█░▀█▀░█▀█░█░█░▀█▀░░░█▀█░█▀▄░█▀▄░█▀█░█░█
// ░█▄█░█▀▄░░█░░░█░░█▀▀░░░█░░░█░█░█░░░█░█░█▀▄░▀▀█░░░░█░░█░█░░░█░█░█░█░░█░░█▀▀░█░█░░█░░░░█▀█░█▀▄░█▀▄░█▀█░░█░
// ░▀░▀░▀░▀░▀▀▀░░▀░░▀▀▀░░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░░░░▀░░▀▀▀░░░▀▀▀░▀▀▀░░▀░░▀░░░▀▀▀░░▀░░░░▀░▀░▀░▀░▀░▀░▀░▀░░▀░
//  copies values from outArray to the led array that will be written to hardware in the main loop
void front_LedStrip::WriteColorsToOutPutArray(CRGB *outArray, bool tl, bool tr, bool bl, bool br, int vertRows)
{	
	if (vertRows == 10)
	{
		if (tl)
		{
			p_objectLedArray[19] = outArray[0];
			p_objectLedArray[18] = outArray[1];
			p_objectLedArray[17] = outArray[2];    
			p_objectLedArray[16] = outArray[3];  
			p_objectLedArray[15] = outArray[4];  
		}
		if (bl)
		{
			p_objectLedArray[14] = outArray[5];  
			p_objectLedArray[13] = outArray[6];  
			p_objectLedArray[12] = outArray[7];  
			p_objectLedArray[11] = outArray[8];  
			p_objectLedArray[10] = outArray[9];
		}
		if (tr)
		{
			p_objectLedArray[0] = outArray[0];
			p_objectLedArray[1] = outArray[1];
			p_objectLedArray[2] = outArray[2];
			p_objectLedArray[3] = outArray[3];
			p_objectLedArray[4] = outArray[4];
		}
		if (br)
		{
			p_objectLedArray[5] = outArray[5];  
			p_objectLedArray[6] = outArray[6];  
			p_objectLedArray[7] = outArray[7];  
			p_objectLedArray[8] = outArray[8];  
			p_objectLedArray[9] = outArray[9];
		}
	}
		
	if (vertRows == 5)
	{
		if (tl)
		{
			p_objectLedArray[19] = outArray[0];
			p_objectLedArray[18] = outArray[1];
			p_objectLedArray[17] = outArray[2];    
			p_objectLedArray[16] = outArray[3];  
			p_objectLedArray[15] = outArray[4]; 
		}
		if (bl)
		{
			p_objectLedArray[14] = outArray[0];  
			p_objectLedArray[13] = outArray[1];  
			p_objectLedArray[12] = outArray[2];  
			p_objectLedArray[11] = outArray[3];  
			p_objectLedArray[10] = outArray[4];
		}
		if (tr)
		{
			p_objectLedArray[0] = outArray[0];
			p_objectLedArray[1] = outArray[1];
			p_objectLedArray[2] = outArray[2];
			p_objectLedArray[3] = outArray[3];
			p_objectLedArray[4] = outArray[4];
			p_objectLedArray[5] = outArray[5];
		}
		if (br)
		{
			p_objectLedArray[5] = outArray[0];
			p_objectLedArray[6] = outArray[1];
			p_objectLedArray[7] = outArray[2];
			p_objectLedArray[8] = outArray[3];
			p_objectLedArray[9] = outArray[4];
		}
	}
};

			// ░█▀▀░█░░░░░░░█▀▀░█░█░█░░░█░░░░░█▀▀░█░█░█▀▀░▀█▀░█▀▀░█▄█░░░█░░░█▀▀░█▀▄░█▀▀
			// ░█░░░█░░░▄▄▄░█▀▀░█░█░█░░░█░░░░░▀▀█░░█░░▀▀█░░█░░█▀▀░█░█░░░█░░░█▀▀░█░█░▀▀█
			// ░▀▀▀░▀▀▀░░░░░▀░░░▀▀▀░▀▀▀░▀▀▀░░░▀▀▀░░▀░░▀▀▀░░▀░░▀▀▀░▀░▀░░░▀▀▀░▀▀▀░▀▀░░▀▀▀        

// ░█▀▀░█▀█░█▀█░█░█░░░█▀█░█▀▀░█▀█░█▀▀░█▀▀░▀█▀░░░▀█▀░█▀█░░░█▀▀░█░█░▀█▀░█▀▀░█▀▄░█▀█░█▀█░█░░░░░█▀█░█▀▄░█▀▄░█▀█░█░█
// ░█░░░█░█░█▀▀░░█░░░░█▀█░▀▀█░█▀▀░█▀▀░█░░░░█░░░░░█░░█░█░░░█▀▀░▄▀▄░░█░░█▀▀░█▀▄░█░█░█▀█░█░░░░░█▀█░█▀▄░█▀▄░█▀█░░█░
// ░▀▀▀░▀▀▀░▀░░░░▀░░░░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░░▀░░░░░▀░░▀▀▀░░░▀▀▀░▀░▀░░▀░░▀▀▀░▀░▀░▀░▀░▀░▀░▀▀▀░░░▀░▀░▀░▀░▀░▀░▀░▀░░▀░
void full_SystemLeds::CopyAspectFanToExternalArray(int fanNumber, CRGB* extArray)
{
	for (int i = 0; i < ASPECTFANLEDS; i++)
	{		
		extArray[i] = virtualAspectFan[fanNumber].leds[i];
		//Serial.println("CFTEA");
		//SerialPrintColor(extArray[0]);
	}
}

void full_SystemLeds::CopyFanToExternalArray(int fanNumber, CRGB* extArray)
{
	for (int i = 0; i < ASPECTFANLEDS; i++)
	{		
		extArray[i] = virtualAspectFan[fanNumber].leds[i];	
	}
}

// ░▀█▀░█▀▄░█▀█░█▀█░█▀▀░█░░░█▀█░▀█▀░█▀▀░░░█▀▀░█▀█░█▄█░█▀▄░▀█▀░█▀█░█▀▀░█▀▄░░░█▀█░█▀▀░█▀█░█▀▀░█▀▀░▀█▀░█▀▀
// ░░█░░█▀▄░█▀█░█░█░▀▀█░█░░░█▀█░░█░░█▀▀░░░█░░░█░█░█░█░█▀▄░░█░░█░█░█▀▀░█░█░░░█▀█░▀▀█░█▀▀░█▀▀░█░░░░█░░▀▀█
// ░░▀░░▀░▀░▀░▀░▀░▀░▀▀▀░▀▀▀░▀░▀░░▀░░▀▀▀░░░▀▀▀░▀▀▀░▀░▀░▀▀░░▀▀▀░▀░▀░▀▀▀░▀▀░░░░▀░▀░▀▀▀░▀░░░▀▀▀░▀▀▀░░▀░░▀▀▀
//translates a populated combined2AspectFans array into 2 separate 1-dimension elements of aspectFansLeds
/*
void full_SystemLeds::TranslateCombinedAspectsToIndividualFans(int fan1, int fan2)
{
	aspectFansLeds[fan1][3] = combined2AspectFans [0];
	aspectFansLeds[fan1][2] = combined2AspectFans [1];
	aspectFansLeds[fan1][1] = combined2AspectFans [2];
	aspectFansLeds[fan2][3] = combined2AspectFans [3];
	aspectFansLeds[fan2][2] = combined2AspectFans [4];
	aspectFansLeds[fan2][1] = combined2AspectFans [5];
	aspectFansLeds[fan1][4] = combined2AspectFans [6];
	aspectFansLeds[fan1][5] = combined2AspectFans [7];
	aspectFansLeds[fan1][0] = combined2AspectFans [8];
	aspectFansLeds[fan2][4] = combined2AspectFans [9];
	aspectFansLeds[fan2][5] = combined2AspectFans [10];
	aspectFansLeds[fan2][0] = combined2AspectFans [11];	
}; */
// assuming that fan 2 is above fan 1:
// the order that combined2AspectFans will be translated
// to the aspectFansLeds array is as below
// LEFT  | RIGHT 
//  5		11
//  4		10
//  3		9
//  2		8
//  1		7
//  0		6

			// ░█▀▀░█░░░░░░░█▀▀░█░█░█▀▀░▀█▀░█▀▀░█▄█░░░▀█▀░▀█▀░█▄█░█▀▀░█▀▄
			// ░█░░░█░░░▄▄▄░▀▀█░░█░░▀▀█░░█░░█▀▀░█░█░░░░█░░░█░░█░█░█▀▀░█▀▄
			// ░▀▀▀░▀▀▀░░░░░▀▀▀░░▀░░▀▀▀░░▀░░▀▀▀░▀░▀░░░░▀░░▀▀▀░▀░▀░▀▀▀░▀░▀

void system_Timer::UpdateSystemTimer()
{
	pastMillis = currentMillis;
	currentMillis = millis();
	deltaMillis = currentMillis - pastMillis;
}

int system_Timer::GetDeltaMillis()
{
	return deltaMillis;
};