#include "LIGHTINGFORDOGGOS.H"

//LIGHTING FUNCTIONS



//NOT LIGHTING FUNCTIONS

//ConvertToPercentageof255
//Arithmetic, General purpose
//Handy for converting timing paramter in RGB control fuctions
//For converting numbers into percentages on a 255 scale
//Accepts two ints as parameters and performs the following operations
//Determines what percentage of 'whole' is represented by 'part'
//calculates what number that percentage of 255 would be
//returns that number
int ConvertToPercentageOf255(int part, int whole)
  {
    float partPercentageOfWhole = ((float)part / (float)whole);
    float floatPortionOf255 = partPercentageOfWhole * 255;
    int portionOf255 = (int)floatPortionOf255;
    return portionOf255;
  }
  
  //FUNCTIONS ARE GROUPED AS FOLLOWS (fan/strip functions call on timing, utility, and color functions)
/////////////////////////
//* UTILITY FUNCTIONS 
//    PrintAspectFanState - Debugging: prints colors assigned to each LED of an Aspect fan
//    PrintFunctionDebugData - Debugging: prints data for the calling effects function. Intended to be placed at beginning of 
//        function after timing check and uncommented as needed
//    SerialPrintColor - prints formatted R G B values of color passed as parameter, then prints end line
//    SerialPrintVars - Debugging: prints 5 int vars in a formatted way
/////////////////////////
//* TIMING AND CONTROL FUNCTIONS
//    AssignFuncDataSlot - returns the first unoccupied index number for the various funcDataX timing/control arrays - IN PROGRESS
//    CheckForRandomColor - management of random color use and creation
//    FrameAdvance - management of frame number advancement for LED functions
//    TimingDrawAddCheck - management of frame write timing for LED functions
/////////////////////////
//* COLOR MANIPULATION OR CREATION RELATED FUNCTIONS
//    MakeRandomColor - returns a color with random RGB values
/////////////////////////
//* SINGLE FAN FUNCTIONS
//    FanNewtonsCradle - one light stays in place while a second moves around the fan. Can do a new color with each revolution
//    FanSpin - makes 1, 2, or 3 lights spin around a fan
//    FanSpinColorWave - Sequentially lights LEDs around an Aspect fan, with a new color each 6 frames
//    FanSpinFill - sequentially writes a color to the LEDs on an Aspect fan
//    FanSpinFillEmpty - sequentially "fills" then "empties" (sets to black) a fan with a color
//    FanVertMovingLine - moves a horizontal line of light up and down a fan
//////////////////////////
//* MULTIPLE FAN FUNCTIONS
//    FrontFanAlternateLoop / in progress, but not working out so well
//    FrontFansBlank / write black to all LEDs in two front fans
//    FrontFansVertBounce / moves a horizontal line of light up and down the two front case fans
//////////////////////////
//* LED STRIP FUNCTIONS
//    TransColorsScrollingFrontLeds - scrolls trans colors on the front LED strips

////////////////////////////////////////////////////
//STANDARD FORMAT OF INPUT FOR SINGLE FAN FUNCTIONS//
//Param 0: speed (minimum milliseconds passed to step forward a frame)
//Param 1: timingSlot (assigns an index number to use for state tracking arrays)
//Param 2: device (determines which fan the function will run on)
//Param 3: color (black for random)
//Param X: other necessary parameters
//STANDARD FORMAT OF INPUT FOR FRONT FAN FUNCTIONS//
//Param 0: speed (minimum milliseconds passed to step forward a frame)
//Param 1: timingSlot (assigns an index number to use for state tracking arrays)
//Param 2: color (black for random)
//Param X: other necessary parameters
//STANDARD FORMAT OF INPUT FOR STRIP FUNCTIONS//
//Param 0: speed (minimum milliseconds passed to step forward a frame)
//Param 1: timingSlot (assigns an index number to use for state tracking arrays)
//Param X: other necessary parameters 

//////////////////////
//UTILITY FUNCTIONS///
//////////////////////

///////////////////////
//====PrintAspectFanState
//PARAMETERS: deviceNumber: the device number of the fan to run this on
void PrintAspectFanState(int deviceNumber)
{
  Serial.println();
  Serial.print("DATA FROM ASPECT FAN NUMBER ");
  Serial.println(deviceNumber);
  for (int i = 0; i < 6; i ++)
  {
    Serial.print("LED");
    Serial.print(i);
    Serial.print(" ");
    SerialPrintColor(largeFans[deviceNumber][i]);
  }

}
///////////////////////
//====PrintFunctionDebugData
//PARAMETERS: funcName: string to output name of functionto debugging print blocks.
      //timingSlot: state tracking array index passed by calling effects function
      //bool color: whether saved color is printed    //bool accMillis: whether accumulated millis are printed
void PrintFunctionDebugData(char funcName[], int timingSlot, int speed, bool timeSlot, bool color, bool accMillis, int device = 100)
{
  Serial.println();
  Serial.print("DATA FROM ");
  Serial.println(funcName);
  if (true)
  {
    Serial.print(device);
    Serial.println(": device number");
  }
  if (true)
  {
    Serial.print(speed);
    Serial.println(": speed");
  }
  
  if (timeSlot)
  {
    Serial.print(timingSlot);
    Serial.println(": timing slot number");
  }
  if (accMillis)
  {
    Serial.print(funcDataMillis[timingSlot]);
    Serial.println(": Accumulated Millis");
  }
  Serial.print(funcDataFrame[timingSlot]);  
  Serial.println(": Frame number");
  if (color)
    SerialPrintColor(funcDataColor[timingSlot]);
  return;
}

///////////////////////
//====SerialPrintColor
//Accepts a CRGB variable and prints its red, green, and blue values in a formatted way, then prints a newline
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
//====SerialPrintVars
//makes debugging via serial.print suck a bit less ass
//accepts up to 5 int vars, prints them on one line with | in between them, then prints a new line
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

////////////////////////////////
//TIMING AND CONTROL FUNCTIONS//
////////////////////////////////

//AssignFuncDataSlot  --  IN PROGRESS
//
/*
int AssignFuncDataSlot()
{
  Serial.println();
  Serial.println("DATA FROM ASSIGNFUNCDATASLOT");
  for (int i = 0; i < 10; i++)
  {
    if (!funcDataSlotOccupied[i])
    {
      funcDataSlotOccupied[i] = true;
      return i;
    }
  }
}
*/

///////////////////////
//====CheckForRandomColor
//FUNCTIONS CALLED - MakeRandomColor - no parameters
//PARAMETERS: same as calling effects function
//Runs at the start of effects functions that can accept a random color
//accepts speed, timingSlot, FRAMELIMIT, color from calling effects function
//In the call to ARC, the calling function MUST assign the returned color to its state tracking array so that ARC can return that color
//    in conditions where a new random color should not be generated
//*If the color passed to the effects function is black AND the frame number is the last frame of the animation
//    ARC generates and returns a random color
//*On other frame numbers, or with other colors
//    ARC returns the color already stored in the effects function's state tracking array
CRGB CheckForRandomColor(int speed, int timingSlot, const int FRAMELIMIT, CRGB color)
{
  //0th condition: if a color is passed to CFRC, write that color to state tracking array for effect and exit
  if (color != CRGB::Black)
    return color;

  //First condition: positive speed, color is black, starting frame - returns new random color
  if ( (speed >= 0) && (color == CRGB::Black) && (funcDataFrame[timingSlot] == 0) ) //if this was called after FrameAdvance, this would be -1
    return MakeRandomColor();  
 
  //Second condition: negative speed, color is black, starting frame - returns new random color
  else if ( (speed < 0) && (color == CRGB::Black) && (funcDataFrame[timingSlot] == FRAMELIMIT -1) ) //if this was called after FrameAdvance, this would be FRAMELIMIT
    return MakeRandomColor();
   
  //Third condition: anything else - returns the color already in the state tracking array, which will have been put there by this function previously
  else
    return funcDataColor[timingSlot];  
}

///////////////////////
//====FrameAdvance
//PARAMETERS: same as calling effects function
//Advance frame at the end of an animation function. If the animation has reached the end, loop the frame number to start over
//Frame number is incremented or decremented (if speed is negative) by one. 
//With positive speed:
//    If frame number is FRAMELIMIT frame number is reset to 0 
//With negative speed:
//    If frame number is -1, frame number is reset to FRAMELIMIT -1
void FrameAdvance(int speed, int timingSlot, int FRAMELIMIT)
{  
  if (speed >= 0)  //code block for positive speed
  {
    funcDataFrame[timingSlot]++;    //increment frame number by 1
    if (funcDataFrame[timingSlot] == FRAMELIMIT)  //check to see if function reached end of effect
      {
        funcDataFrame[timingSlot] = 0;   //reset frame to 0 to loop the effect
        return;
      }
  }
  else if (speed < 0)  //code block for negative speed
  {
    funcDataFrame[timingSlot]--;    //decrement frame number by 1
    if (funcDataFrame[timingSlot] == -1)  //check to see if function reached end of effect
    {
      funcDataFrame[timingSlot] = (FRAMELIMIT -1);      //reset frame to FRAMELIMIT -1 to loop the effect
      return;    
    }
  }  
}

///////////////////////
//====TimingDrawAddCheck
//PARAMETERS: same as calling effects function
//Called at the beginning of effects functions to determine whether to simply update passed time or execute a frame write
//1: adds deltaMills to accumulated millis for the calling function (funcDataMillis[timingSlot])
//2: checks speed (or speed * -1 if negative) against accumulated millis
//3A: if accumulated millis is smaller than speed, return false and exit
//3B: if accumulated millis is => speed, set accumulated millis to zero, return true and exit
//Typically, the calling function will exit if TimingDrawAddCheck returns false
//If the calling function has subframes, it will evaluate the true/false return to determine how to proceed
bool TimingDrawAddCheck (int speed, int timingSlot)
{  
  funcDataMillis[timingSlot] += deltaMillis; //1: adds deltaMillis to accumulated millis
  
  if (speed < 0) //if speed is negative, change to positive for in-function comparison
    speed *= -1;

  if (funcDataMillis[timingSlot] < speed) //2: compares accumulated millis to speed
    return false; //3A: return false if accumulated millis is less than speed 
  
  funcDataMillis[timingSlot] = 0;  //3B: a frame has been written: reset accumulated millis to 0 and return true
  return true;  
}

//////////////////////////////
//COLOR-RELATED FUNCTIONS/////
//////////////////////////////

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

////////////////////////
//SINGLE FAN FUNCTIONS//
////////////////////////
//in single fan functions, device is translated to the one of the fans that are part of the
//largefans array: 2 front (#0 on the bottom and #1 on the top) and one  on the back (#2)

///////////////////////
//====FanNewtonsCradle
//PARAMETERS: | speed: time between frames in milliseconds 
//    timingSlot: index number to track data in state tracking arrays for this effect | device: which of 3 fans this effect will run on
//    color: the color to use in this effect. (This will mostly be black/random, otherwise it's kind of boring)
//This puts a solid dot of light on one LED while another light moves around the fan until it comes back to the stationary one.
//    Then the stationary one changes to the next color and the process repeats
void FanNewtonsCradle(int speed, int timingSlot, int device, CRGB color)
{  
  const int FRAMELIMIT = 6; //number of frames in this effect

  //manage frame write timing
  if ( !TimingDrawAddCheck(speed, timingSlot) )  
    return;  
 
  PrintFunctionDebugData("FanNewtonsCradle",timingSlot, speed, 1, 1, 0, device); //uncomment to display debugging data with timeslot and saved color

  //generate random color based on frame and speed
  funcDataColor[timingSlot] = CheckForRandomColor(speed, timingSlot, FRAMELIMIT, CRGB::Black); 

  //Black out the fan before calculating frame
  for (int i = 0; i < 6; i++)
    largeFans[device][i] = CRGB::Black;
  
  largeFans[device][0] = funcDataColor[timingSlot];//Light the starting LED
  largeFans[device][ (funcDataFrame[timingSlot] ) ] = funcDataColor[timingSlot]; //light the moving LED
  
  FrameAdvance(speed, timingSlot, FRAMELIMIT); //advance frame as appropriate
}

///////////////////////
//====FanSpin
//PARAMETERS: | speed: time between frames in milliseconds 
//    timingSlot: index number to track data in state tracking arrays for this effect | device: which of 3 fans this effect will run on
//    CRGB colors 1, 2, and 3: colors to use in the effect. 2 and 3 are optional, and will make additional lights appear to spin if present
//    startFrame: in progress
//simple function to make leds light move sequentially around a fan, one position at a time
//If passed one, two, or three colors, one, two, or three light(s) is/are used. 
//This function does not support randomized colors
void FanSpin(int speed, int timingSlot, int device, CRGB color, CRGB color2 = CRGB::Black, CRGB color3 = CRGB::Black, int startFrame = 0)
{  
  const int FRAMELIMIT = 6; //number of frames in this animation
  int numberOfLights = 1;  //the number of LEDs to use in the spinning animation - 1 by default

  //if more than one color was passed, add LEDs up to 3 to the spin animation
  if (color2 != CRGB::Black)
    numberOfLights++;
  if (color3 != CRGB::Black)
    numberOfLights++;
  
  if ( !TimingDrawAddCheck(speed, timingSlot) )  //manage frame write timing
    return;

  PrintFunctionDebugData("FanSpin", timingSlot, speed, 1, 0, 1, device); //uncomment to display debugging data with timeslot and accumulated millis
  
  //write black to all LEDs to prepare for writing the next frame
  for (int i = 0; i < 6; i++)   
    largeFans[device][i] = CRGB::Black;
  
  //write color to LEDs according to current frame number stored in array and number of lights
  //for 1 light: always runs
  largeFans[device][ (funcDataFrame[timingSlot] ) ] = color;

  //for 2 lights only
  if (numberOfLights == 2)          
    largeFans[device][ (funcDataFrame[timingSlot] + 9 ) % 6 ] = color2;  //LEDs are separated by 3, i.e. 0 and 3
  
  //for 3 lights only
  else if (numberOfLights == 3)     
  {
    largeFans[device][ (funcDataFrame[timingSlot] + 8 ) % 6 ] = color2;  //LEDs are separated by 2, i.e. 0, 2, and 4
    largeFans[device][ (funcDataFrame[timingSlot] + 10 ) % 6 ] = color3;
  }  
 
  FrameAdvance(speed, timingSlot, FRAMELIMIT); //advance frame as appropriate
}

///////////////////////
//FanSpinColorWave
//PARAMETERS: | speed: time between frames in milliseconds 
//    timingSlot: index number to track data in state tracking arrays for this effect | device: which of 3 fans this effect will run on   
//Lights each LED around an Aspect fan sequentially, leaves them on, and repeats with a new color
//non-selectable color: always random
void FanSpinColorWave(int speed, int timingSlot, int device)
{
  const int FRAMELIMIT = 6; //set number of frames in the animation  
  
  if ( !TimingDrawAddCheck(speed, timingSlot) )  //manage frame write timing
    return;  

  //generate random color based on frame and speed. Black is hard-coded to pass to CFRC because this function currently always uses a random color
  funcDataColor[timingSlot] = CheckForRandomColor(speed, timingSlot, FRAMELIMIT, CRGB::Black); 

  largeFans[device][ funcDataFrame[timingSlot] ] = funcDataColor[timingSlot]; //light LED corresponding to frame number

  FrameAdvance(speed, timingSlot, FRAMELIMIT); //advance frame as appropriate
}

///////////////////////
//FanSpinFill  Successively write a color to each LED on an Aspect fan
//PARAMETERS: | speed: time between frames in milliseconds 
//    timingSlot: index number to track data in state tracking arrays for this effect | device: which of 3 fans this effect will run on
//    color: the color for the effect to use 
//TO DO: write a separate empty function to write black, so that this function can be used with random colors

void FanSpinFill(int speed, int timingSlot, int device, CRGB color)
{  
  const int FRAMELIMIT = 6; //number of frames in this animation

  if ( !TimingDrawAddCheck(speed, timingSlot) )  //manage frame write timing
    return;

  funcDataColor[timingSlot] = color; //saving passed color in state tracking array

  largeFans[device][ funcDataFrame[timingSlot] ] = funcDataColor[timingSlot]; //LED# frame is light on device number : WTF does this comment mean?

  FrameAdvance(speed, timingSlot, FRAMELIMIT);  //advance frame as appropriate
}


///////////////////////
//FanSpinFillEmpty fills a fan successivly with a color, then empties it successively
//PARAMETERS: | speed: time between frames in milliseconds 
//    timingSlot: index number to track data in state tracking arrays for this effect | device: which of 3 fans this effect will run on
//    colors: the color to use in displaying this effect (black for random)
//    reverseEmpty: whether the second "empty" part of the effect runs in the opposite direction of the first "fill" part
//TO DO: rewrite to accept two speeds: one for fill, one for empty?
void FanSpinFillEmpty(int speed, int timingSlot, int device, CRGB color, int reverseEmpty = 0)
{
  const int FRAMELIMIT = 12; //frames in this animation
  
  if ( !TimingDrawAddCheck(speed, timingSlot) )  //manage frame write timing   
    return;      

  funcDataColor[timingSlot] = CheckForRandomColor(speed, timingSlot, FRAMELIMIT, color); //manage random color use  
 
  //Fill portion
  if (funcDataFrame[timingSlot] <= 5) //frames 0 through 5 are the fill portion
    largeFans[device][ funcDataFrame[timingSlot] ] = funcDataColor[timingSlot];
  
  //empty portion
  else if (funcDataFrame[timingSlot] <= 11)
  {
    if (!reverseEmpty)  //simply turns off LEDs in the same order they were turned on
     largeFans[device][ (funcDataFrame[timingSlot]) % 6 ] = CRGB::Black;
    else if (reverseEmpty)
    {
      int ledReverseOrder[6] = {5,3,1,-1,-3,-5}; //offsets to apply sequentially to calculated value to reverse order of LEDs 
      largeFans[device][ ((funcDataFrame[timingSlot]) % 6) + ledReverseOrder[funcDataFrame[timingSlot] % 6] ] = CRGB::Black;      
    }
  }  

  FrameAdvance(speed, timingSlot, FRAMELIMIT); //advance frame as necessary
}

/////////////////////////
//FanVertMovingLine
//PARAMETERS: | speed: time between frames in milliseconds 
//    timingSlot: index number to track data in state tracking arrays for this effect | device: which of 3 fans this effect will run on
//    color: the color to use in displaying this effect (black for random)
//    startFrame: in progress
//Causes a color to move across the fan from top to bottom (reversible) using top two LEDs, then middle two,
//then bottom two
void FanVertMovingLine(int speed, int timingSlot, int device, CRGB color, int startFrame = 0)
{
  const int FRAMELIMIT = 4;
  if ( !TimingDrawAddCheck(speed, timingSlot) )
    return;
  
  //black out all LEDs before writing frame
  for (int i = 0; i < 6; i++)
    largeFans[device][i] = CRGB::Black;

  //light correct LEDs by frame
  if (funcDataFrame[timingSlot] == 0)
  {
    largeFans[device][3] = color;
    largeFans[device][4] = color;
  }
  else if ((funcDataFrame[timingSlot] == 1) || (funcDataFrame[timingSlot] == 3))
  {
    largeFans[device][2] = color;
    largeFans[device][5] = color;  
  }
  else if (funcDataFrame[timingSlot] == 2)
  {
    largeFans[device][1] = color;
    largeFans[device][0] = color;    
  }
  
  FrameAdvance(speed, timingSlot, FRAMELIMIT);  //advance frame as appropriate      
}

//////////////////////////
//MULTIPLE FAN FUNCTIONS//
//////////////////////////

///////////////////////
//FrontFanAlternateLoop
//Does some cool stuff. In progress.
void FrontFanAlternateLoop(int speed, int timingSlot, CRGB color0, CRGB color1)
{
  const int FRAMELIMIT = 140;

  if ( !TimingDrawAddCheck(speed, timingSlot) )  //manage frame write timing
    return;

  //debugging info
  Serial.println();
  Serial.println("INFORMATION FROM FRONTFANALTERNATELOOP");
  Serial.print("Frame number: ");
  Serial.println(funcDataFrame[timingSlot]);
  Serial.print("Frame number % 2 is: ");
  Serial.println(funcDataFrame[timingSlot] % 2);

  FrontFansBlank(); //black all LEDs in front fans
   
  //Frames 0 - 19
  //"spin" the two colors around for 20 frames by alternating which LED has which on odd vs even frames
  if (funcDataFrame[timingSlot] < 20)
  {
    if ((funcDataFrame[timingSlot] % 2) == 0)
    {
      for (int i = 0; i < 6; i++)
      {
        if (i % 2 == 0)  
        {
          largeFans[0][i] = color1;           
        }
        else if (i % 2 == 1)  
          largeFans[0][i] = color0; 
      }
    }
    else if ((funcDataFrame[timingSlot] % 2) == 1)
    {
      for (int i = 0; i < 6; i++)
      {
        if (i % 2 == 0)  
        {
          largeFans[0][i] = color0;            
        }
        else if (i % 2 == 1)  
          largeFans[0][i] = color1; 
      }
    }
  }
    
  //Frames 20 - 59
  //continue to spin 3 LEDs of color 0 and 2 LEDs of color 1 while 1 LED of color one moves up to fan 1  

  //Moving one LED up to the top of the upper fan
  else if (funcDataFrame[timingSlot] < 60)
  {
    //Moving the single LED up to the middle - 10 frames per step)
    if (funcDataFrame[timingSlot] < 30)    
      largeFans[1][3] = color1;    
    else if (funcDataFrame[timingSlot] < 40)
      largeFans[1][2] = color1;
    else if (funcDataFrame[timingSlot] < 50)
      largeFans[1][1] = color1;
    else if (funcDataFrame[timingSlot] < 60)    
      largeFans[1][0] = color1;      
        
    //Keep spinning the lights on the fan
    //EVEN FRAMES
    if ((funcDataFrame[timingSlot] % 2) == 0) //Determining odd vs. even, so acting on even frames
    {
      for (int i = 0; i < 6; i++) //once for each LED on the fan
      {
        if (i % 2 == 0)  //Determining odd vs. even, so acting on all even numbered LEDs
        {
          if (i < 3) //all even LEDs lower than 5 get color1 - LEDs 0,2
          {
            largeFans[0][i] = color1;      
            Serial.print("Color 1 on LED ");
            Serial.println(i);
          }
        }
        else if (i % 2 == 1)  //Determining odd vs. even, so acting on all odd numbered LEDs
          largeFans[0][i] = color0;  //runs on every odd LED placing color 0 - LEDs 1,3,5
      }
    }
    else if ((funcDataFrame[timingSlot] % 2) == 1) //Determining odd vs. even, so acting on odd frames
    {
      for (int i = 0; i < 6; i++) //once for each LED on the fan
      {
        if (i % 2 == 0)  //Determining odd vs. even, so acting on all even numbered LEDs
        {
          largeFans[0][i] = color0;  //all even LEDS get color0 - LEDs 0, 2, 4
        }
        else if (i % 2 == 1)  //Determining odd vs. even, so acting on all odd numbered LEDs
        {
          if (i < 5)         
          {
            largeFans[0][i] = color1;      //all odd LEDs lower than 5 get color1 - LEDs 1,3
            Serial.print("Color 1 on LED ");
            Serial.println(i);
          }
        }
      }
    }
  }
  //Frames 60 - 99
  //continue to spin 3 LEDs of color 0 and 1 LED of color 1 while the second LED of color one moves up to fan 1
  else if (funcDataFrame[timingSlot] < 100)
  {
    ////LED at spot [1][0] stays in place
    largeFans[1][0] = color1; 
  
    //Moving another single LED up to the middle - 10 frames per step)
    if (funcDataFrame[timingSlot] < 70)
    {
      largeFans[1][3] = color1;
      Serial.println("Lighting [1][3]");     
    }
    else if (funcDataFrame[timingSlot] < 80)
    {
      largeFans[1][2] = color1;
      Serial.println("Lighting [1][2]");
    }
    else if (funcDataFrame[timingSlot] < 100) //Moving LED stops at LED number [1][1] Because [1][0] is already on
    {
      largeFans[1][1] = color1;
      Serial.println("Lighting [1][1]");
    }    
    
    //Keep spinning the lights on the fan
    if ((funcDataFrame[timingSlot] % 2) == 0) //Determining odd vs. even, so acting on even frames
    {
      for (int i = 0; i < 6; i++) //once for each LED on the fan
      {
        if (i % 2 == 0)  //Determining odd vs. even, so acting on all even numbered LEDs
        {
          if (i < 2) //runs on even LEDs 0-1, placing color1 - LEDs 0,2
            largeFans[0][i] = color1;          
        }
        else if (i % 2 == 1)  //runs on every odd LED placing color 0 - LEDs 1,3,5
          largeFans[0][i] = color0;   //every odd LED gets color 0
      }
    }
    else if ((funcDataFrame[timingSlot] % 2) == 1) //Determining odd vs. even, so acting on odd frames
    {
      for (int i = 0; i < 6; i++) //once for each LED on the fan
      {
        if (i % 2 == 0)  //Determining odd vs. even, so acting on all even numbered LEDs        
          largeFans[0][i] = color0;  //all even LEDS get color0 - LEDs 0, 2, 4        
        else if (i % 2 == 1)  //Determining odd vs. even, so acting on all odd numbered LEDs
          if (i < 3) 
            largeFans[0][i] = color1; //all odd LEDs lower than 5 get color1 - LEDs 1,3
      }
    }
  }

    //Frames 100-139
  //continue to spin 3 LEDs of color 0 and 0 LEDs of color 1 while the third LED of color one moves up to fan 1
  else if (funcDataFrame[timingSlot] < 140)
  {
    ////LEDs at spot [1][0] and [1][1] stay in place
    largeFans[1][0] = color1; 
    largeFans[1][1] = color1; 
  
    //Moving another single LED up to the middle - 10 frames per step)
    if (funcDataFrame[timingSlot] < 110)
    {
      largeFans[1][3] = color1;
      Serial.println("Lighting [1][3]");     
    }
    else if (funcDataFrame[timingSlot] < 120)
    {
      largeFans[1][2] = color1;
      Serial.println("Lighting [1][2]");
    }
    //LED merges with spot [1][1] after frame 79
    
    //Keep spinning the lights on the fan
    if ((funcDataFrame[timingSlot] % 2) == 0) //Determining odd vs. even, so acting on even frames
    {
      for (int i = 0; i < 6; i++) //once for each LED on the fan
      {
        //Only need to act on odd LEDs - there are no more color1 lights left on the fan
        if (i % 2 == 1)  //runs on every odd LED placing color 0 - LEDs 1,3,5
          largeFans[0][i] = color0;   //every odd LED gets color 0
      }
    }
    else if ((funcDataFrame[timingSlot] % 2) == 1) //Determining odd vs. even, so acting on odd frames
    {
      for (int i = 0; i < 6; i++) //once for each LED on the fan
      {
        //Only need to act on even LEDs - there are no more color1 lights left on the fan
        if (i % 2 == 0)  //Determining odd vs. even, so acting on all even numbered LEDs        
          largeFans[0][i] = color0;  //all even LEDS get color0 - LEDs 0, 2, 4           
      }
    }
  }
  
  FrameAdvance(speed, timingSlot, FRAMELIMIT);  //advance frame as appropriate    

}

///////////////////////
//FrontFansBlank
//PARAMETERS: none
//Write black to all LEDs on the two front case fans
//This is generally called by other effects functions to clear the LEDs at the beginning of each frame write
void FrontFansBlank()
{ 
for (int i = 0; i < 2; i++)
  for (int j = 0; j < 6; j++)
    largeFans[i][j] = CRGB:: Black; //i is device number, j is LED number
}

//FrontFansVertBounce
//PARAMETERS: | speed: time between frames in milliseconds 
//    timingSlot: index number to track data in state tracking arrays for this effect 
//    color: the color to use in displaying the effect (black for random) | startFrame: in progress
//Moves a horizintal line, hopefully in a coordinated way, up and down across both front case fans
//TO DO - rewrite as calls to two functions: one for fill one for empty
//TO DO - Fix the coordination by figuring out how to set a starting frame for the FanVertMovingLine function?
//TO DO - rewrite to use state tracking color array instead of an internal color variable
void FrontFansVertBounce(int speed, int timingSlot, CRGB color, int startFrame = 0)
{ 
  const int FRAMELIMIT = 10;  //number of frames in this animation
  CRGB internalColor; //to store color after checking for random color option

  if ( !TimingDrawAddCheck(speed, timingSlot) )  //manage frame write timing
    return;

  if (color == CRGB::Black)
  {
    if ((funcDataFrame[timingSlot] == 0) || (funcDataFrame[timingSlot] == 5))  //if random color, change it on frames 0 and 5
    {
      internalColor = MakeRandomColor();
    }
  }
  else
    internalColor = color;   
 
  //turn off all LEDs on front fans at the beginning of each frame
  FrontFansBlank();

  //then write to the ones that should be on
  if (funcDataFrame[timingSlot] == 0)
  {
    largeFans[1][0] = internalColor;
    largeFans[1][1] = internalColor;
  }
  else if ((funcDataFrame[timingSlot] == 1) || (funcDataFrame[timingSlot] == 9))
  {
    largeFans[1][2] = internalColor;
    largeFans[1][5] = internalColor;
  }
  else if ((funcDataFrame[timingSlot] == 2) || (funcDataFrame[timingSlot] == 8))
  {
    largeFans[1][3] = internalColor;
    largeFans[1][4] = internalColor;
  }
  else if ((funcDataFrame[timingSlot] == 3) || (funcDataFrame[timingSlot] == 7))
  {
    largeFans[0][0] = internalColor;
    largeFans[0][1] = internalColor;
  }
  else if ((funcDataFrame[timingSlot] == 4) || (funcDataFrame[timingSlot] == 6))
  {
    largeFans[0][2] = internalColor;
    largeFans[0][5] = internalColor; 
  }
  else if (funcDataFrame[timingSlot] == 5)
  {
    largeFans[0][3] = internalColor;
    largeFans[0][4] = internalColor;
  } 
   
  FrameAdvance(speed, timingSlot, FRAMELIMIT);  //advance frame as appropriate
}

/////////////////////////
//LED STRIP FUNCTIONS////
/////////////////////////

/////////////////////////
//StripRandomFlashing
//PARAMETERS: | speed: time between frames in milliseconds 
//    timingSlot: index number to track data in state tracking arrays for this effect
//    color: color to use for effect (black for random on each frame)
//TO DO: fix random color generation to happen on each LED instead of each frame
void StripRandomFlashing(int speed, int timingSlot, CRGB color)
{
  const int FRAMELIMIT = 20;  //number of frames in this effect
  int currentLED = -1; //to track which LED is lit this frame. 
  int randomNumber; //for use in randomizing LED order

  if ( !TimingDrawAddCheck(speed, timingSlot) )  //manage frame write timing   
    return;      

  PrintFunctionDebugData("STRIPRANDOMFLASHING", timingSlot, speed, 1, 1, 1); //uncomment to display debugging data - shows timeslot, millis, and color

  for (int i = 0; i < 20; i++) //sets all front strip LEDs to black. This should be rewritten as a function like the one for the front fans
    ledStrip[i] = CRGB::Black;

  funcDataColor[timingSlot] = CheckForRandomColor(speed, timingSlot, FRAMELIMIT, color); //manage randon color use    

  randomNumber = (rand() % 20);
  if (! funcDataStripLedTracking[randomNumber])
  {
    funcDataStripLedTracking[randomNumber] = true;
    ledStrip[randomNumber] = funcDataColor[timingSlot];
  }
  else
    {
      do
      {
        randomNumber = (rand() % 20);
      } while (funcDataStripLedTracking[randomNumber]);
      funcDataStripLedTracking[randomNumber] = true;
      ledStrip[randomNumber] = funcDataColor[timingSlot];
    } 
    
  funcDataStripLedTracking[randomNumber] = 1;  
  ledStrip[randomNumber] = funcDataColor[timingSlot];

  if (funcDataFrame[timingSlot] == 19)
  {
    for (int i = 0; i < 20; i++)
    {
      funcDataStripLedTracking[i] = 0;
    }   
  }

  FrameAdvance(speed, timingSlot, FRAMELIMIT);  //advance frame as appropriate
}

/////////////////////////
//TransColorsScrollingFrontLeds
//PARAMETERS: | speed: time between frames in milliseconds 
//    timingSlot: index number to track data in state tracking arrays for this effect
//    CRGB colors 1, 2, and 3: colors to use in the effect | side: whether the effect displays on both sides, left side, or right side
//Accepts three colors, arranges them in 0-1-2-1-0 order, and scrolls them on the front LED strips
void TransColorsScrollingFrontLeds(int speed, int timingSlot, CRGB color0, CRGB color1, CRGB color2, int side = 0)
{ 
  const int FRAMELIMIT = 8;  //number of frames of animation in this function
  bool nextFrame = 1; //checks whether to advance to the next frame at the end of the function  
  float change; //to track the amount of blending to apply to colors based on elapsed millis between frames
  float changePerMilli = 255 / (float)speed;  //how much change is applied per elapsed milli between frames
  if (changePerMilli < 0)
    changePerMilli *= -1;  //making changePerMilli positive in case passed speed is negative

  if ( !TimingDrawAddCheck(speed, timingSlot) )  
    nextFrame = 0;

  //PrintFunctionDebugData("TransColorsScrollingFrontLeds", timingSlot, speed, 1, 0, 1); //uncomment to display debugging data with timeslot and accumulated millis
    
  CRGB baseArray[10];  //creating array to hold basecolors and blended colors
  CRGB outArray[10];  //Array to hold colors ready to write out to LEDs

  //holding base colors in correct order with gaps between for blends
  baseArray[0] = color0;  //blue  //red for testing
  baseArray[2] = color1;  //pink  //green for testing
  baseArray[4] = color2;  //white  //blue for testing
  baseArray[6] = color1;  //pink  //green for testing
  baseArray[8] = baseArray[0];  //line 8 will always duplicate line 0
  //holding blends of base colors in correct order
  baseArray[1] = blend( color0, color1, 128 );  //blue to pink  //red to green for testing
  baseArray[3] = blend( color1, color2, 128 );  //pink to white  //green to blue for testing
  baseArray[5] = blend( color1, color2, 128 );  //pink to white  //green to blue for testing
  baseArray[7] = blend( color0, color1, 128 );  //blue to pink  //red to green for testing
  baseArray[9] = baseArray[1]; //line 9 will always duplicate line 1
  //baseArray[9] = blend( color0, color1, 128 );  //blue to Pink
  
  change = funcDataMillis[timingSlot] * changePerMilli;  //how much blending to apply based on elapsed millis
  //between frames

  //manage frame write timing. Most functions return if TimingDrawAddCheck is false, but this one needs to process
  //subrames (color blending) between frames. So rather than return, it sets a flag if the frame should advance
  //The rest of the function executes the same way in either condition, except that if TimingDrawAddCheck is true
  //then the frame number is advanced at the end, which sets up the next set of subframes.
  //nextFrame is set true by default, and then set to 0 if not enough millis have passed to advance.
     
   //for positive speed
  if (speed >= 0)
    for (int i = 0; i < 8; i++)
      outArray[i] = blend( (baseArray[ (i + 8 + funcDataFrame[timingSlot]) % 8 ]),(baseArray[ (i + 1 + 8 + funcDataFrame[timingSlot]) % 8 ]),change);     
  
  //negative speed requires applying (10 - framenumber) instead of framenumber because I can't make the frames
  //iterate backwards without rewriting the FrameAdvance function. And just doing the 10 - offset is so simple
  //but I need to explain that here before I forget why it's there.
  //The (10 -) inverts the number, making 1 into 9, or 9 into 1.
  else if (speed < 0)  
    for (int i = 0; i < 8; i++)
      outArray[i] = blend( (baseArray[ ((i - (8 - funcDataFrame[timingSlot])) + 10) % 8 ]),(baseArray[ ((i - 1 - (8 - funcDataFrame[timingSlot])) + 10 ) % 8 ]),change);

  //left vs. right vs both is controlled by a parameter passed at invocation
  if (side == 0 || side == 1)
  {
    //write left side  
    ledStrip[19] = outArray[0];
    ledStrip[18] = outArray[1];
    ledStrip[17] = outArray[2];    
    ledStrip[16] = outArray[3];  
    ledStrip[15] = outArray[4];  
    ledStrip[14] = outArray[5];  
    ledStrip[13] = outArray[6];  
    ledStrip[12] = outArray[7];  
    ledStrip[11] = outArray[0];  
    ledStrip[10] = outArray[1];
  }
  if (side == 0 || side == 2)
  {
    //write right side
    ledStrip[0] = outArray[0];
    ledStrip[1] = outArray[1];
    ledStrip[2] = outArray[2];
    ledStrip[3] = outArray[3];
    ledStrip[4] = outArray[4];
    ledStrip[5] = outArray[5];
    ledStrip[6] = outArray[6];
    ledStrip[7] = outArray[7];
    ledStrip[8] = outArray[0];
    ledStrip[9] = outArray[1];
  }

  if (nextFrame)
    FrameAdvance(speed, timingSlot, FRAMELIMIT);  //advance frame as appropriate
}