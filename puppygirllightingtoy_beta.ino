//#include <FastLED.h>
#include "globalsfordoggos.h"
#include "classesfordoggos.h"
#include "functionsfordoggos.h"
//#include <variablesfordoggos.h>

//constant declarations reflecting hardware parameters
const int LARGEFANLEDS = 6;  //Number of LEDs on the chassis fans
const int SMALLFANLEDS = 4;  //Number of LEDs on the CPU fan
const int GREATESTLEDS = 6;  //Highest number of LEDs on a single device
const int NUM_DEVICES = 5;   //The number of separate LED devices being controlled.
const int NUM_FANS = 4;

//constant data pin number declarations
#define DATA_PIN2 2
#define DATA_PIN4 4
#define DATA_PIN7 7
#define DATA_PIN8 8
#define DATA_PIN9 9

// var declarations for arrays of LEDs. These get written to each loop of the program, then at the end they all get written to the LEDs.
// First, this array is for the two fans on the front of the case and the one on the back to make it easier to coordinate effects on them.
// These three are Aspect fans with 6 LEDs each
//CRGB largeFans[3][LARGEFANLEDS]; //  -  Now declared/defined in globalsfordoggos.h
//CRGB* p_LargeFansArray = &largeFans;
// Following are individual devices: details after each one
CRGB fan3[SMALLFANLEDS];  //CPU cooling fan, 4 LEDs
CRGB ledStrip[20]; //Front panel LEDs: 20 at the moment. 

// variable speeds to attach to functions
// TO-DO
// move these into globals, write some functions to create values for them in functionsfordoggos
int variableSpeed = 0; 
int variableSpeed2 = 0;
int speedDivider = 0;

cpu_Fan cpuFan0;            // instantiating an object for CPU fan
aspect_Fan aspectFan0;      // instantiating an object for Aspect fan 0
aspect_Fan aspectFan1;      // instantiating an object for Aspect fan 1
aspect_Fan aspectFan2;      // instantiating an object for Aspect fan 2
front_LedStrip ledStrip0;   // instantiating an object for front LED strip
dual_FrontAspectFans frontFans; // // instantiating an object for dual front fans

// FOR DEBUGGING
int testValue0;
int testValue1;
int testValue2;
int testValue3;

// EFFECTS TEST FUNCTIONS: run one effect on all fans
void TestMovingLine(int speed, CRGB* color)
{  
  aspectFan0.MovingLine(speed, color);
  aspectFan1.MovingLine(speed, color);
  aspectFan2.MovingLine(speed, color);
  cpuFan0.MovingLine(speed, color);
}

void TestSpinColorWave(int speed, CRGB* color)
{
  aspectFan0.SpinColorWave(speed,color);
  aspectFan1.SpinColorWave(speed,color);
  aspectFan2.SpinColorWave(speed,color);
  cpuFan0.SpinColorWave(speed * 1.5,color);
}
void TestSpinOneLed(int speed, CRGB* palette)
{
  aspectFan0.SpinOneLed(speed, palette);
  aspectFan1.SpinOneLed(speed, palette);
  aspectFan2.SpinOneLed( (-1 * speed), palette);
  cpuFan0.SpinOneLed(speed, palette);
}

void TestSpinLeds(int speed, CRGB color1, CRGB color2 = CRGB:: Black, CRGB color3 = CRGB:: Black)
{
  aspectFan0.SpinLeds(speed, color1, color2, color3);
  aspectFan1.SpinLeds(-speed, color1, color2, color3);
  aspectFan2.SpinLeds(speed, color1, color2, color3);
  cpuFan0.SpinLeds(speed * 1.5, color1, color2, color3);
}

void TestFadeThroughColors(int speed, CRGB* palette)
{
  aspectFan0.FadeThroughColors(speed, palette); 
  aspectFan1.FadeThroughColors(speed, palette); 
  aspectFan2.FadeThroughColors(speed, palette); 
  cpuFan0.FadeThroughColors(speed, palette);
}

void setup() 
{
  srand(millis());
  //Adding RGB LEDs
  FastLED.addLeds<NEOPIXEL, DATA_PIN2>(largeFans[0], LARGEFANLEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PIN4>(largeFans[1], LARGEFANLEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PIN7>(largeFans[2], LARGEFANLEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PIN8>(fan3, SMALLFANLEDS);          // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PIN9>(ledStrip, 20);                // GRB ordering is assumed
  FastLED.setBrightness(255);                                        //Set overall brightness on scale of 255

  //Power-on delay
  delay(2000);
  //Open serial port for debugging  Serial.begin(9600); 
}    

void loop() {
  //Serial.println();
  //Serial.println("Main loop beginning");

  UpdateSystemTimer();  // update deltaMillis based on passing of time since last main loop

  //stuff dealing with values for passing to functions as speed 
  //oscillation, sort of, of variable speed to pass to functions in lieu of a constant speed
  if (variableSpeed < 400)
  {
    speedDivider++;
    if (speedDivider == 7)
    {
      variableSpeed++;
      speedDivider = 0;
    }
  }  
  else
    variableSpeed = -400;

  variableSpeed2 = variableSpeed + 400;
  if (variableSpeed2 > 400)
    variableSpeed2 -= 800;
  
  //FAN TEST FUNCTIONS
  //TestMovingLine(200, prideLesbian);
  //TestSpinLeds(variableSpeed, CRGB::Blue, CRGB::Purple);
  //TestSpinOneLed(-80, prideLesbian);
  //TestSpinColorWave(100,blackForRandom);
  //TestSpinColorWave(-100,prideLesbian);
  //aspectFan2.SpinColorWaveFade(100, singleGreen, 0.35);

  // to remember what the counter values of the led strip were before running the effects methods on them
  testValue0 = ledStrip0.topLeftFrameNumber;
  testValue1 = ledStrip0.topRightFrameNumber;
  testValue2 = ledStrip0.bottomLeftFrameNumber;
  testValue3 = ledStrip0.bottomRightFrameNumber;

  // ASPECT FAN EFFECT CALLS
  //TestFadeThroughColors(2000, prideLesbian);

  // CPU FAN EFFECT CALLS  

  // FRONT STRIP EFFECT CALLS    
  //ledStrip0.BlinkLeds(1000,rgbTest);
  //ledStrip0.ScrollColorsOnFrontStrips(-400, prideLesbian,0,1,0,1);
  //ledStrip0.ScrollColorsOnFrontStrips(-400, prideLesbian,1,0,1,0);

  //ledStrip0.ScrollColorsOnFrontStrips(400, prideTransgender,0,1,0,1);
  //ledStrip0.ScrollColorsOnFrontStrips(400, prideTransgender,1,0,1,0);

  //ledStrip0.ChaseWithFade(40, prideLesbian, .8, 2);

  // CURRENT EFFECTS SHOW
  
  int secondsPerPhase = (currentMillis / 20000) % 3;
  
  if (secondsPerPhase == 0)    //run for 15 seconds
  {
    ledStrip0.ScrollColorsOnFrontStrips(200, prideLesbian,1,0,1,0);
    ledStrip0.ScrollColorsOnFrontStrips(-200, prideLesbian,0,1,0,1);
    aspectFan0.SpinLeds(100, prideLesbian[0],prideLesbian[4]);
    aspectFan1.SpinLeds(-100, prideLesbian[4], prideLesbian[0]);
    aspectFan2.FadeThroughColors(2000, prideLesbian);
    cpuFan0.FadeThroughColors(2000, prideLesbian);
  }
  else if (secondsPerPhase == 1)
  {
    ledStrip0.ScrollColorsOnFrontStrips(400, prideTransgender,0,1,0,1);
    ledStrip0.ScrollColorsOnFrontStrips(-400, prideTransgender,1,0,1,0);
    aspectFan0.SpinLeds(variableSpeed, prideTransgender[0],prideTransgender[1]);
    aspectFan1.SpinLeds(variableSpeed2 * -1, prideTransgender[1], prideTransgender[0]);
    aspectFan2.SpinColorWave(variableSpeed, prideTransgender);
    //cpuFan0.SpinColorWave(variableSpeed * 1.5, prideTransgender);
    cpuFan0.FadeThroughColors(2000, prideTransgender);
  }
  else
  {
    ledStrip0.ChaseWithFade(40, prideRainbow, .8, 2);
    aspectFan0.SpinColorWave(100, prideRainbow);
    aspectFan1.SpinColorWave(100, prideRainbow);
    aspectFan2.FadeThroughColors(2000, prideRainbow);
    cpuFan0.FadeThroughColors(2000, prideRainbow);
  }
  


  //aspectFan2.BlinkLeds(25, singlePurple);

  
  //// DEBUG CODE - if any of the counters for the led strip have changed, print the values of all of them
  /*
  if ( (ledStrip0.topLeftFrameNumber != testValue0) || (ledStrip0.topRightFrameNumber != testValue1) || (ledStrip0.bottomLeftFrameNumber != testValue2) || (ledStrip0.bottomRightFrameNumber != testValue3)  )
  {
    Serial.println();
    Serial.print("SC: topLeftFrameNumber is: ");
    Serial.println(ledStrip0.topLeftFrameNumber);
    Serial.print("SC: topRightFrameNumber is: ");
    Serial.println(ledStrip0.topRightFrameNumber);
    Serial.print("SC: bottomLeftFrameNumber is: ");
    Serial.println(ledStrip0.bottomLeftFrameNumber);
    Serial.print("SC: bottomRightFrameNumber is: ");	
    Serial.println(ledStrip0.bottomRightFrameNumber);	
  }
  */

  //frontFans.StackFill(50, prideTransgender);
  //frontFans.TranslateLedsToOutPutArray();

  // Write finished colors out to hardware arrays
  for (int i = 0; i < 6; i++)             //Aspect Fans
  {
    largeFans[0][i] = aspectFan0.leds[i];   
    largeFans[1][i] = aspectFan1.leds[i];    
    largeFans[2][i] = aspectFan2.leds[i];       

    // for dual front fan object
    /*
    largeFans[0][i] = frontFans.dualFans[0][i];
    largeFans[1][i] = frontFans.dualFans[1][i];
    */
  } 
  for (int i = 0; i < 4; i++)             //CPU fan
    fan3[i] = cpuFan0.leds[i];   
  for (int i = 0; i < 20; i++)            //Front LED strip
    ledStrip[i] = ledStrip0.leds[i];      //assigning member variables from strip object to array that is written out to hardware at end of main loop
  
  //write updated arrays to LEDs for display
  FastLED.show();
  //delay(1000); //uncomment this line to add a delay to make troubleshooting via output statements easier. Delay should not affect timing of 
  //properly written functions because they are comparing to millis passed.  
}
