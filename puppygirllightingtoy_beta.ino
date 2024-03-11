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

//Creating arrays to hold timer data, frame number data, and other things I was using static variables for that didn't work out
//elements are referenced by the timing slot number sent to each function that uses the arrays
//funcDataMillis tracks accumulated millis until frame write, then resets
//funcDataFrame tracks the frame number the function's animation sequence is on
//funcDataInit tracks whether the function has used a one-time frame number init value (IN PROGRESS)
//funcDataSlotOccupied tracks whether its index number has been assigned to a function (IN PROGRESS)
//funcDataColor tracks a CRGB color between function calls
//funcDataStripLedTracking is for tracking things like randomization of strip LEDs without repetition
int funcDataMillis[30];
int funcDataFrame[30];
bool funcDataInit[30];
bool funcDataSlotOccupied[30];
CRGB funcDataColor[30];
bool funcDataStripLedTracking[20]; 

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

  //ASPECT FANS
  aspectFan0.AddElapsedTimeToTotal(deltaMillis);
  aspectFan1.AddElapsedTimeToTotal(deltaMillis);
  aspectFan2.AddElapsedTimeToTotal(deltaMillis);


  if (((currentMillis / 6000) % 2) == 0)    //run forward for 10 seconds
  {
    aspectFan0.SpinOneLed(90, CRGB::Black);
    aspectFan1.SpinOneLed(-75, CRGB::Black);
    aspectFan2.SpinOneLed(120, CRGB::Black);
  }
  else                                      //run backward for 10 seconds  
  {
    aspectFan0.SpinOneLed(-90, CRGB::Black);
    aspectFan1.SpinOneLed(50, CRGB::Black);
    aspectFan2.SpinOneLed(-200, CRGB::Black);
  }
 
  

  //CPU FAN    
  cpuFan0.AddElapsedTimeToTotal(deltaMillis);

  if (((currentMillis / 6000) % 2) == 0)    //run forward for 10 seconds
    cpuFan0.SpinOneLed(90, CRGB::Black);
  else  
    cpuFan0.SpinOneLed(-90, CRGB::Black);   //run backward for 10 seconds

  // Write finished colors out to fan hardware arrays

  for (int i = 0; i < 6; i++)
  {
    largeFans[0][i] = aspectFan0.leds[i];   
    largeFans[1][i] = aspectFan1.leds[i];    
    largeFans[2][i] = aspectFan2.leds[i];    
  }
  
  for (int i = 0; i < 4; i++)  //copy internal array (leds[]) to external array(fan3[]) for writing to hardware at end of main loop
    fan3[i] = cpuFan0.leds[i];   
  
  //write updated arrays to LEDs for display
  FastLED.show();
  //delay(1000); //uncomment this line to add a delay to make troubleshooting via output statements easier. Delay should not affect timing of 
  //properly written functions because they are comparing to millis passed.
}

