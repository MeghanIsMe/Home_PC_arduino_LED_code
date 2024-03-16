/*
  
*/

// include LED control library
#include "FastLED.h"
#include "functionsfordoggos.h"

// include this library's description file
#include "classesfordoggos.h"

//**********************************************************************************************************************
//**********************************************************************************************************************
//**************************************** GENERIC LED DEVICE CLASS************************************************************
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
void generic_LedDevice::CheckInitialization()
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
bool generic_LedDevice::CheckTimeForFrameDraw(int speed)  
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
void generic_LedDevice::FrameAdvance(int speed, int FRAMELIMIT)
{
	if (frameNumber > FRAMELIMIT)				 // if another effect left the frame number too high, reset to 0
		frameNumber = 0;
		
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




//**********************************************************************************************************************
//**********************************************************************************************************************
//**************************************** GENERIC FAN CLASS************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************

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
};


//**********************************************************************************************************************
//**********************************************************************************************************************
//**************************************** CPU FAN CLASS****************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************

//**********************************************************************************************************************
//**********************************************************************************************************************
//**************************************** FRONT LED STRIP CLASS********************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************


// UTILITY FUNCTIONS

///////////////////////
//==== WriteToOutGoingArray
// 
void front_LedStrip::WriteToOutgoingArray(int side, CRGB *outArray)
{
	if (side == 0 || side == 1)
  {
    //write left side  
    leds[19] = outArray[0];
    leds[18] = outArray[1];
    leds[17] = outArray[2];    
    leds[16] = outArray[3];  
    leds[15] = outArray[4];  
    leds[14] = outArray[5];  
    leds[13] = outArray[6];  
    leds[12] = outArray[7];  
    leds[11] = outArray[0];  
    leds[10] = outArray[1];
  }
  if (side == 0 || side == 2)
  {
    //write right side
    leds[0] = outArray[0];
    leds[1] = outArray[1];
    leds[2] = outArray[2];
    leds[3] = outArray[3];
    leds[4] = outArray[4];
    leds[5] = outArray[5];
    leds[6] = outArray[6];
    leds[7] = outArray[7];
    leds[8] = outArray[0];
    leds[9] = outArray[1];
  }
}

// EFFECTS FUNCTIONS

///////////////////////
//==== BlankLeds
// 
void front_LedStrip::BlankLeds()
{
	for (int i = 0; i < NUMLEDS; i++)
		leds[i] = CRGB::Black;
};
	
///////////////////////
//==== BlinkLeds
// 
void front_LedStrip::BlinkLeds(int speed, CRGB color)
{
	const int FRAMELIMIT = 2;		// frames in this animation
	
	if (!CheckTimeForFrameDraw(speed)) // manage frame write timing
		return;
		
	savedColor = CheckForRandomColor(color, savedColor, FRAMELIMIT, frameNumber, speed);  //manage random color use
	
	BlankLeds();			// set all LEDs to black before writing frame
	
	if (frameNumber == 0)		// On frame 0, set all LEDs on with saved color
		for (int i = 0; i < NUMLEDS; i++)		// once for each LED
			leds[i] = savedColor;
		
	FrameAdvance(speed, FRAMELIMIT);		// manage frame advancement
};

///////////////////////
//==== TransColorsScrollingFrontLeds
// 
void front_LedStrip::TransColorsScrollingFrontLeds(int speed, CRGB *palette, int side)
{
	const int FRAMELIMIT = 8; 	// update this to programmatically determine based on array passed to function
	bool nextFrame = 1; 		 	// flag to advance frame at end of function
	float change; 						// to track amount of blending to apply to colors based on elapsed millis between frames
	float changePerMilli = 255 / (float)speed;  //how much change is applied per millisecond
	CRGB baseArray[10];  		  //creating array to hold basecolors and blended colors
  CRGB outArray[10];  			//Array to hold colors ready to write out to LEDs
		
	if (changePerMilli < 0)  	// convert to positive change in case of negative speed
		changePerMilli *= -1;
	
	if (!CheckTimeForFrameDraw(speed)) // manage frame write - if false, function progresses with between-frame blending
		nextFrame = 0;									 // but will not advance frame
		
	//holding base colors in correct order with gaps between for blends
  baseArray[0] = palette[0];  //blue  //red for testing
  baseArray[2] = palette[1];  //pink  //green for testing
  baseArray[4] = palette[2];  //white  //blue for testing
  baseArray[6] = palette[1];  //pink  //green for testing
  baseArray[8] = baseArray[0];  //line 8 will always duplicate line 0
  //holding blends of base colors in correct order
  baseArray[1] = blend( palette[0], palette[1], 128 );  //blue to pink  //red to green for testing
  baseArray[3] = blend( palette[1], palette[2], 128 );  //pink to white  //green to blue for testing
  baseArray[5] = blend( palette[1], palette[2], 128 );  //pink to white  //green to blue for testing
  baseArray[7] = blend( palette[0], palette[1], 128 );  //blue to pink  //red to green for testing
  baseArray[9] = baseArray[1]; //line 9 will always duplicate line 1
	
	change = accumulatedMilliseconds * changePerMilli;  //how much blending to apply based on elapsed milliseconds between frames
	
	 //for positive speed
  if (speed >= 0)
    for (int i = 0; i < 8; i++)
      outArray[i] = blend( (baseArray[ (i + 8 + frameNumber) % 8 ]),(baseArray[ (i + 1 + 8 + frameNumber) % 8 ]),change);     
  
  //negative speed requires applying (10 - framenumber) instead of framenumber because I can't make the frames
  //iterate backwards without rewriting the FrameAdvance function. And just doing the 10 - offset is so simple
  //but I need to explain that here before I forget why it's there.
  //The (10 -) inverts the number, making 1 into 9, or 9 into 1.
  else if (speed < 0)  
    for (int i = 0; i < 8; i++)
      outArray[i] = blend( (baseArray[ ((i - (8 - frameNumber)) + 10) % 8 ]),(baseArray[ ((i - 1 - (8 - frameNumber)) + 10 ) % 8 ]),change);

	
	//left vs. right vs both is controlled by a parameter passed at invocation
	//WriteToOutgoingArray(side, outArray);
	if (side == 0 || side == 1)
  {
    //write left side  
	  leds[19] = outArray[0];
    leds[18] = outArray[1];
    leds[17] = outArray[2];    
    leds[16] = outArray[3];  
    leds[15] = outArray[4];  
    leds[14] = outArray[5];  
    leds[13] = outArray[6];  
    leds[12] = outArray[7];  
    leds[11] = outArray[0];  
    leds[10] = outArray[1];
		
  }
  if (side == 0 || side == 2)
  {
    //write right side
    leds[0] = outArray[0];
    leds[1] = outArray[1];
    leds[2] = outArray[2];
    leds[3] = outArray[3];
    leds[4] = outArray[4];
    leds[5] = outArray[5];
    leds[6] = outArray[6];
    leds[7] = outArray[7];
    leds[8] = outArray[0];
    leds[9] = outArray[1];
  }
	
	if (nextFrame)
    FrameAdvance(speed, FRAMELIMIT);  //advance frame as appropriate
	
}

///////////////////////
//==== ScrollColors
//  Scrolls a set of colors passed in via an array on one or more quarters of the front LED strips
//  This is called by ScrollColorsOnFrontStrips
//			// SCOFS determines the number of vertical rows and passes the booleans determing which parts of the strips to run on
//	Accepts an array of colors to use
//	Creates an array of double that length (baseArray) which includes blends of colors between the ones on the input array
//	Does math to write baseArray's values into outArray in the correct order based on frame number
//	Calls WriteColorsToOutPutArray to write outArray to the calling object's LED array
void front_LedStrip::ScrollColors(int speed, CRGB *palette, int vertRows, bool tl, bool tr, bool bl, bool br)
{
	int lengthOfInputArray = (GetLengthOfBlackTerminatedCRGBArray(palette));; // the number of colors in the passed array
	int lengthOfBaseArray = lengthOfInputArray * 2;		// the base array holds the input array plus blends	
	int count = 1; 														// math for assigning blended colors to baseArray
	const int FRAMELIMIT = lengthOfBaseArray; // how many frames until positions of input array colors repeat
	float change; 						// to track amount of blending to apply to colors based on elapsed millis between frames
	float changePerMilli = 255 / (float)speed;  //how much change is applied per millisecond
	bool nextFrame = 1; 		 								  // flag to advance frame at end of function
	CRGB baseArray[lengthOfBaseArray];  		  //creating array to hold basecolors and blended colors
  CRGB outArray[vertRows];  						  	//Array to hold colors ready to write out to LEDs
	CRGB blendColor; 												  // to temporarily hold color to write to outarray
			
	if (changePerMilli < 0)  	// convert to positive change in case of negative speed
		changePerMilli *= -1;
	
	if (!CheckTimeForFrameDraw(speed)) // manage frame write - if false, function progresses with between-frame blending
			nextFrame = 0;									 // but will not advance frame
	
	change = changePerMilli * accumulatedMilliseconds;  // how much change/blending to apply this function iteration
					
	// populating base array
	for (int i = 0; i < lengthOfBaseArray; i++) // once for each color + each color blend
	{		
		if (i % 2 == 0)														// even lines (and 0) get colors directly from input array
			baseArray[i] = palette[ (i / 2) % lengthOfInputArray];
		else if (i % 2 == 1)											// odd lines get blends of colors from input array
		{	
			baseArray[i] = blend( palette[ (i - count) % lengthOfInputArray], palette[ (i - count + 1) % lengthOfInputArray], 128);
			count++;			
		}		
	}

 // for positive speed
  if (speed >= 0)
    for (int i = 0; i < vertRows; i++)  //once for each hardware row
		{							
      outArray[i] = blend(
									 (baseArray[ (i + frameNumber) % lengthOfBaseArray ]),      // argument 1
									 (baseArray[ (i + 1 + frameNumber) % lengthOfBaseArray ]),  // argument 2
									 change);																						  			// argument 3
		}     
	// for negative speed
	else if (speed < 0)  
			for (int i = 0; i < vertRows; i++)
			{				
				outArray[i] = blend(
										 (baseArray [(i - (lengthOfBaseArray - frameNumber) + 10) % lengthOfBaseArray  ]),		  // argument 1
										 (baseArray [(i - 1 - (lengthOfBaseArray - frameNumber) + 10) % lengthOfBaseArray ]),   // argument 2
										  change);																										 													// argument 3		
			}		
	WriteColorsToOutPutArray(outArray, tl, tr, bl, br, vertRows);
	
	//debugging
	Serial.print("Length of base array is: ");
	Serial.println(lengthOfBaseArray);
	Serial.print("Frame number: ");
	Serial.println(frameNumber);
	Serial.println();
	
	if (nextFrame)
    FrameAdvance(speed, FRAMELIMIT);  //advance frame as appropriate	
}

///////////////////////
//==== ScrollColorsOnFrontStrips
//  Calls ScrollColors and provides the booleans passed to this argument plus the number of vertical rows determined in this function
void front_LedStrip::ScrollColorsOnFrontStrips(int speed, CRGB *palette, bool tl, bool tr, bool bl, bool br)
{
	int vertRows;	
	if ( ( (tl) || (tr) ) && ( (bl) || (br) ) )  // if at least one upper and one lower strip are engaged, 10 rows. Else, 5.
		vertRows = 10;
	else
		vertRows = 5;	
	
	front_LedStrip::ScrollColors(speed, palette, vertRows, tl, tr, bl, br);	
}

///////////////////////
//==== WriteColorsToOutputArray
// 
void front_LedStrip::WriteColorsToOutPutArray(CRGB *outArray, bool tl, bool tr, bool bl, bool br, int vertRows)
{
	Serial.print("top left: ");
	Serial.println(tl);
	Serial.print("top right: ");
	Serial.println(tr);
	Serial.print("bottom left: ");
	Serial.println(bl);
	Serial.print("bottom right: ");
	Serial.println(br);
	
	if (vertRows == 10)
	{
		if (tl)
		{
			leds[19] = outArray[0];
			leds[18] = outArray[1];
			leds[17] = outArray[2];    
			leds[16] = outArray[3];  
			leds[15] = outArray[4];  
		}
		if (bl)
		{
			leds[14] = outArray[5];  
			leds[13] = outArray[6];  
			leds[12] = outArray[7];  
			leds[11] = outArray[8];  
			leds[10] = outArray[9];
		}
		if (tr)
		{
			leds[0] = outArray[0];
			leds[1] = outArray[1];
			leds[2] = outArray[2];
			leds[3] = outArray[3];
			leds[4] = outArray[4];
		}
		if (br)
		{
			leds[5] = outArray[5];  
			leds[6] = outArray[6];  
			leds[7] = outArray[7];  
			leds[8] = outArray[8];  
			leds[9] = outArray[9];
		}
	}
		
	if (vertRows == 5)
	{
		if (tl)
		{
			leds[19] = outArray[0];
			leds[18] = outArray[1];
			leds[17] = outArray[2];    
			leds[16] = outArray[3];  
			leds[15] = outArray[4]; 
		}
		if (bl)
		{
			leds[14] = outArray[0];  
			leds[13] = outArray[1];  
			leds[12] = outArray[2];  
			leds[11] = outArray[3];  
			leds[10] = outArray[4];
		}
		if (tr)
		{
			leds[0] = outArray[0];
			leds[1] = outArray[1];
			leds[2] = outArray[2];
			leds[3] = outArray[3];
			leds[4] = outArray[4];
			leds[5] = outArray[5];
		}
		if (br)
		{
			leds[5] = outArray[0];
			leds[6] = outArray[1];
			leds[7] = outArray[2];
			leds[8] = outArray[3];
			leds[9] = outArray[4];
		}
	}
};






 