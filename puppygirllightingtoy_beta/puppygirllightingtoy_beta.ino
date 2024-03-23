//#include <FastLED.h>
#include <classesfordoggos.h>
#include <functionsfordoggos.h>

//constant declarations reflecting hardware parameters
const int LARGEFANLEDS = 6;  //Number of LEDs on the chassis fans
const int SMALLFANLEDS = 4;  //Number of LEDs on the CPU fan
const int GREATESTLEDS = 6;  //Highest number of LEDs on a single device
const int NUM_DEVICES = 5;   //The number of separate LED devices being controlled.
const int NUM_FANS = 4;

//constant color declarations
const CRGB NICEBLUE = CRGB(0, 120, 255);
const CRGB TRANSBLUE = CRGB(91,206,250);
const CRGB TRANSPINK = CRGB(245,169,184); 
const CRGB TRANSWHITE = CRGB(128,128,128);

//  UTILITY COLOR ARRAYS
CRGB blackForRandom[] = {CRGB::Black};

// SINGLE COLOR ARRAYS
CRGB singlePurple[] = {CRGB::Purple, CRGB::Black};
CRGB singleGreen[] = {CRGB::Green, CRGB::Black};

//  PRIDE COLOR ARRAYS/PALETTES
CRGB prideBisexual[] = {CRGB(214,2,112), CRGB(155,79,150), CRGB(0,56, 168), CRGB::Black};
CRGB prideBisexualBreak[] = {CRGB(214,2,112), CRGB(155,79,150), CRGB(0,56, 168), CRGB(0,0,1), CRGB::Black};
CRGB prideRainbow[] = {CRGB(228,3,3),CRGB(255,140,0),CRGB(255,237,0),CRGB(0,128,38),CRGB(26,64,142),CRGB(115,41,130),CRGB::Black};
CRGB prideTransgender[] = {CRGB::Turquoise, CRGB::DeepPink, CRGB::Linen, CRGB::DeepPink, CRGB::Black};
CRGB prideTransgenderBreak[] = {CRGB::Turquoise, CRGB::DeepPink, CRGB::Linen, CRGB::DeepPink, CRGB::Turquoise, CRGB(0,0,1), CRGB::Black};
CRGB prideLesbian[] = {CRGB(214,46,2),CRGB(184, 60, 8),CRGB(253,152,85),CRGB(125,38,87),CRGB(125,5,82),CRGB::Black};
CRGB prideLesbianBreak[] = {CRGB(214,46,2),CRGB(184, 60, 8),CRGB(253,152,85),CRGB(125,38,87),CRGB(125,5,82),CRGB(0,0,1),CRGB(0,0,1),CRGB::Black};

//  TEST COLOR ARRAYS
CRGB rgbTest[] = {CRGB::Red, CRGB::Lime, CRGB::Blue, CRGB::Black};
CRGB redBlueTest[] = {CRGB::Red, CRGB::Blue, CRGB::Black};

//constant data pin number declarations
#define DATA_PIN2 2
#define DATA_PIN4 4
#define DATA_PIN7 7
#define DATA_PIN8 8
#define DATA_PIN9 9

// var declarations for arrays of LEDs. These get written to each loop of the program, then at the end they all get written to the LEDs.
// First, this array is for the two fans on the front of the case and the one on the back to make it easier to coordinate effects on them.
// These three are Aspect fans with 6 LEDs each
CRGB largeFans[3][LARGEFANLEDS];
// Following are individual devices: details after each one
CRGB fan3[SMALLFANLEDS];  //CPU cooling fan, 4 LEDs
CRGB ledStrip[20]; //Front panel LEDs: 20 at the moment. 

// var declarations for timing.
// pastMillis begins at 0. Each loop, pastMillis gets the value from current Millis, then currentMillis gets value from millis(),
// then deltaMillis = currentMillis - pastMills. The result is the number of milliseconds that have passed since the last execution
// of the loop. I pass deltaMillis to effect functions, where it is added to a running total. TimingDrawAddCheck is called at the beginning
// of effects functions to see if the total is greater than the time between steps (also passed to them, called speed)
// If so, the function executes a frame. Else, it is skipped (with an exception for functions that have subframes)
unsigned long currentMillis = 0;  
unsigned long pastMillis = 0;     
unsigned long deltaMillis = 0;    

// variable speeds to attach to functions
int variableSpeed = 0; 
int variableSpeed2 = 0;
int speedDivider = 0;

cpu_Fan cpuFan0;            // instantiating an object for CPU fan
aspect_Fan aspectFan0;      // instantiating an object for Aspect fan 0
aspect_Fan aspectFan1;      // instantiating an object for Aspect fan 1
aspect_Fan aspectFan2;      // instantiating an object for Aspect fan 2
front_LedStrip ledStrip0;   // instantiating an object for front LED strip

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
  //variables for function timing
  pastMillis = currentMillis;
  currentMillis = millis();
  deltaMillis = currentMillis - pastMillis;  

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
  //aspectFan2.SpinColorWave(-100, prideRainbow);  

  // CPU FAN EFFECT CALLS  

  // FRONT STRIP EFFECT CALLS    
  //ledStrip0.BlinkLeds(1000,rgbTest);
  //ledStrip0.ScrollColorsOnFrontStrips(-400, prideLesbian,0,1,0,1);
  //ledStrip0.ScrollColorsOnFrontStrips(-400, prideLesbian,1,0,1,0);

  //ledStrip0.ScrollColorsOnFrontStrips(400, prideTransgender,0,1,0,1);
  //ledStrip0.ScrollColorsOnFrontStrips(400, prideTransgender,1,0,1,0);

  //ledStrip0.ChaseWithFade(40, prideLesbian, .8, 2);

  int secondsPerPhase = (currentMillis / 20000) % 3;
  
  if (secondsPerPhase == 0)    //run for 15 seconds
  {
    ledStrip0.ScrollColorsOnFrontStrips(200, prideLesbian,1,0,1,0);
    ledStrip0.ScrollColorsOnFrontStrips(-200, prideLesbian,0,1,0,1);
    aspectFan0.SpinLeds(100, prideLesbian[0],prideLesbian[4]);
    aspectFan1.SpinLeds(-100, prideLesbian[4], prideLesbian[0]);
    aspectFan2.SpinColorWave(100, prideLesbian);
    cpuFan0.SpinColorWave(150, prideLesbian);
  }
  else if (secondsPerPhase == 1)
  {
    ledStrip0.ScrollColorsOnFrontStrips(400, prideTransgender,0,1,0,1);
    ledStrip0.ScrollColorsOnFrontStrips(-400, prideTransgender,1,0,1,0);
    aspectFan0.SpinLeds(variableSpeed, prideTransgender[0],prideTransgender[1]);
    aspectFan1.SpinLeds(variableSpeed * -1, prideTransgender[1], prideTransgender[0]);
    aspectFan2.SpinColorWave(variableSpeed, prideTransgender);
    cpuFan0.SpinColorWave(variableSpeed * 1.5, prideTransgender);
  }
  else
  {
    ledStrip0.ChaseWithFade(40, prideRainbow, .8, 2);
    aspectFan0.SpinColorWave(100, prideRainbow);
    aspectFan1.SpinColorWave(100, prideRainbow);
    aspectFan2.SpinColorWave(100, prideRainbow);
    cpuFan0.SpinColorWave(150, prideRainbow);
  }

  
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

  // Write finished colors out to hardware arrays
  for (int i = 0; i < 6; i++)             //Aspect Fans
  {
    largeFans[0][i] = aspectFan0.leds[i];   
    largeFans[1][i] = aspectFan1.leds[i];    
    largeFans[2][i] = aspectFan2.leds[i];       
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

