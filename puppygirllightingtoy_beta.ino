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

//Palette and color group declarations
CRGB transColors[4] = {CRGB::Turquoise, CRGB::DeepPink, CRGB::Linen, CRGB::Black};
//CRGB transColorsTest[6] = {CRGB::Turquoise, CRGB::DeepPink, CRGB::Linen, CRGB::DeepPink, CRGB::Turquoise, CRGB::Black};

CRGB rgbTest[4] = {CRGB::Red, CRGB::Lime, CRGB::Blue, CRGB::Black};
CRGB redBlueTest[3] = {CRGB::Red, CRGB::Blue, CRGB::Black};

CRGB blackForRandom[1] = {CRGB::Black};

//  PRIDE COLOR ARRAYS/PALETTES
CRGB prideBisexual[] = {CRGB(214,2,112), CRGB(155,79,150), CRGB(0,56, 168), CRGB::Black};
CRGB prideBisexualBreak[] = {CRGB(214,2,112), CRGB(155,79,150), CRGB(0,56, 168), CRGB(0,0,1), CRGB::Black};
CRGB prideRainbow[] = {CRGB(228,3,3),CRGB(255,140,0),CRGB(255,237,0),CRGB(0,128,38),CRGB(26,64,142),CRGB(115,41,130),CRGB::Black};
CRGB prideTransgender[] = {CRGB::Turquoise, CRGB::DeepPink, CRGB::Linen, CRGB::DeepPink, CRGB::Black};
CRGB prideTransgenderBreak[] = {CRGB::Turquoise, CRGB::DeepPink, CRGB::Linen, CRGB::DeepPink, CRGB::Turquoise, CRGB(0,0,1), CRGB::Black};
CRGB prideLesbian[] = {CRGB(214,46,2),CRGB(184, 60, 8),CRGB(253,152,85),CRGB(125,38,87),CRGB(125,5,82),CRGB::Black};
CRGB prideLesbianBreak[] = {CRGB(214,46,2),CRGB(184, 60, 8),CRGB(253,152,85),CRGB(125,38,87),CRGB(125,5,82),CRGB(0,0,1),CRGB(0,0,1),CRGB::Black};

// 214,46,2  - starting index 0 color. Could use to be a little darker, and maybe make this into index 1
//200,200,100

//from index 0: 214,46,2

// Index 1: 255,128, 30
// Index 2: 253,152, 85
// Index 4: 125,38,87 (Dark Respeberry)
// Index 5: 135,38,87 (Plum Velvet)


//constant data pin number declarations
#define DATA_PIN2 2
#define DATA_PIN4 4
#define DATA_PIN7 7
#define DATA_PIN8 8
#define DATA_PIN9 9

//var declarations for arrays of LEDs. These get written to each loop of the program, then at the end they all get written to the LEDs.
//First, this array is for the two fans on the front of the case and the one on the back to make it easier to coordinate effects on them.
//These three are Aspect fans with 6 LEDs each
CRGB largeFans[3][6];
//Following are individual devices: details after each one
CRGB fan3[SMALLFANLEDS];  //CPU cooling fan, 4 LEDs
CRGB ledStrip[20]; //Front panel LEDs: 20 at the moment. 

//var declarations for timing.
//pastMillis begins at 0. Each loop, pastMillis gets the value from current Millis, then currentMillis gets value from millis(),
//then deltaMillis = currentMillis - pastMills. The result is the number of milliseconds that have passed since the last execution
//of the loop. I pass deltaMillis to effect functions, where it is added to a running total. TimingDrawAddCheck is called at the beginning
//of effects functions to see if the total is greater than the time between steps (also passed to them, called speed)
//If so, the function executes a frame. Else, it is skipped (with an exception for functions that have subframes)
unsigned long currentMillis = 0;  
unsigned long pastMillis = 0;     
unsigned long deltaMillis = 0;    

//variable speeds to attach to functions
int variableSpeed = 0; //for changing speed on a running function
int variableSpeed2 = 0;

cpu_Fan cpuFan0;  //instanatiating an object for CPU fan
aspect_Fan aspectFan0;  //instantiating an object for Aspect fan 0
aspect_Fan aspectFan1;  //instantiating an object for Aspect fan 1
aspect_Fan aspectFan2;  //instantiating an object for Aspect fan 2
front_LedStrip ledStrip0;  //instantiating an object for front LED strip

int testValue0;
int testValue1;
int testValue2;
int testValue3;

// Effects Test Functions: run one effect on all fans
void TestMovingLine(int speed, CRGB color)
{  
  aspectFan0.MovingLine(speed, color);
  aspectFan1.MovingLine(speed, color);
  aspectFan2.MovingLine(speed, color);
  cpuFan0.MovingLine(speed, color);
}

void TestSpinColorWave(int speed)
{
  aspectFan0.SpinColorWave(speed);
  aspectFan1.SpinColorWave(speed);
  aspectFan2.SpinColorWave(speed);
  cpuFan0.SpinColorWave(speed);
}
void TestSpinOneLed(int speed, CRGB color)
{
  aspectFan0.SpinOneLed(speed, color);
  aspectFan1.SpinOneLed(speed, color);
  aspectFan2.SpinOneLed( (-1 * speed), color);
  cpuFan0.SpinOneLed(speed, color);
}

void TestSpinLeds(int speed, CRGB color1, CRGB color2 = CRGB:: Black, CRGB color3 = CRGB:: Black)
{
  aspectFan0.SpinLeds(speed, color1, color2, color3);
  aspectFan1.SpinLeds(speed, color1, color2, color3);
  aspectFan2.SpinLeds(speed, color1, color2, color3);
  cpuFan0.SpinLeds(speed, color1, color2, color3);
}

void setup() {
  srand(millis());
  //Adding RGBs
  FastLED.addLeds<NEOPIXEL, DATA_PIN2>(largeFans[0], LARGEFANLEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PIN4>(largeFans[1], LARGEFANLEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PIN7>(largeFans[2], LARGEFANLEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PIN8>(fan3, SMALLFANLEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PIN9>(ledStrip, 20);  // GRB ordering is assumed
  //Set overall brightness on scale of 255
  FastLED.setBrightness(255);

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
  if (variableSpeed < 500)
    variableSpeed++;
  else
    variableSpeed = -500;

  variableSpeed2 = variableSpeed + 500;
  if (variableSpeed2 > 500)
    variableSpeed2 -= 1000;
  
  //FAN TEST FUNCTIONS
  //TestMovingLine(variableSpeed, CRGB::Purple);
  //TestSpinLeds(variableSpeed, CRGB::Blue, CRGB::Purple);
  //TestSpinOneLed(variableSpeed, CRGB::Black);
  //TestSpinColorWave(100);

  // to remember what the counter values of the led strip were before running the effects methods on them
  testValue0 = ledStrip0.topLeftFrameNumber;
  testValue1 = ledStrip0.topRightFrameNumber;
  testValue2 = ledStrip0.bottomLeftFrameNumber;
  testValue3 = ledStrip0.bottomRightFrameNumber;

  // ASPECT FAN EFFECT CALLS

  
  aspectFan2.SpinColorWaveTest(100, prideLesbian);

  // CPU FAN EFFECT CALLS
  cpuFan0.SpinColorWaveTest(50, prideRainbow);

  // FRONT STRIP EFFECT CALLS    
  if (((currentMillis / 15000) % 2) == 0)    //run for 15 seconds
  {
    ledStrip0.ScrollColorsOnFrontStrips(200, prideLesbian,1,1,1,1);
    aspectFan0.SpinLeds(100, prideLesbian[0],prideLesbian[4]);
    aspectFan1.SpinLeds(-100, prideLesbian[4], prideLesbian[0]);
  }
  else
  {
    ledStrip0.ScrollColorsOnFrontStrips(400, prideTransgender,1,1,1,1);
    aspectFan0.SpinLeds(100, prideTransgender[0],prideTransgender[1]);
    aspectFan1.SpinLeds(-100, prideTransgender[1], prideTransgender[0]);
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
  //delay(150); //uncomment this line to add a delay to make troubleshooting via output statements easier. Delay should not affect timing of 
  //properly written functions because they are comparing to millis passed.
  
}

