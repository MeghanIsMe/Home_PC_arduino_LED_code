	//ASCII fonts for large comments: 
	//https://www.asciiart.eu/text-to-ascii-art - pagga from ASCII art archive - medium header

#include "FastLED.h"                       // for backend hardware interfacing
#include "globalsfordoggos.h"       // global settings like number of leds per type of fan and similar
#include "ledcontrolfordoggos.h"  //  classes and functions that support and control the lighting effects

// constants to make it easier to see what pin is being by FastLED to connect to arrays
// this is based on hardware setup - how many and what kind of LEDs are connected to the controller
// is fixed by hardware configuration
#define DATA_PIN2 2
#define DATA_PIN4 4
#define DATA_PIN5 5
#define DATA_PIN7 7
#define DATA_PIN8 8
#define DATA_PIN9 9

int foo = 0;

// These are the arrays that are written to hardware by FastLED.show at the end of each main loop
// They have a 1-1 correspondence to the aRGB LED hardware
CRGB stripLeds[LINEARSTRIPLEDS];            // on pin 9
CRGB aspect0Leds[ASPECTFANLEDS];        // on pin 2
CRGB aspect1Leds[ASPECTFANLEDS];        // on pin 4
CRGB aspect2Leds[ASPECTFANLEDS];        // on pin 7
CRGB cpuFanLeds[CPUFANLEDS];              // on pin 8

// Instantiating the object that does most of the work of setting LED colors
full_SystemLeds systemLeds;
// Instantiating the system timer
system_Timer systemTimer;

//int deltaMillis = 0;                                      // For tracking effects timing. Is populated with method from system_Timer class defined in ledcontrolfordoggos 

void setup() {

  delay(8000);              // power on safety delay
  Serial.begin(9600);    // for seriall debugging

// Associating arrays with FastLED. These arrays will be written out to hardware at the end of each main loop
  FastLED.addLeds<WS2812B, DATA_PIN2, GRB>(aspect0Leds,6);
  FastLED.addLeds<WS2812B, DATA_PIN4, GRB>(aspect1Leds,6);
  FastLED.addLeds<WS2812B, DATA_PIN7, GRB>(aspect2Leds,6);
  FastLED.addLeds<WS2812B, DATA_PIN8, GRB>(cpuFanLeds,4);
  FastLED.addLeds<WS2812B, DATA_PIN9, GRB>(stripLeds,20);
 }

void loop() {

  systemTimer.UpdateSystemTimer();
  deltaMillis = systemTimer.GetDeltaMillis();       // deltaMillis is defined in globals for doggos. It is global so that all classes have access to the value for use in timing

  //pastMillis = currentMillis;
  //currentMillis = millis();
  //deltaMillis = currentMillis - pastMillis;  

  //Serial.println(systemTimer.GetDeltaMillis() );

  systemLeds.virtualAspectFan[0].SpinColorWave(50,prideTransgender);
  systemLeds.virtualAspectFan[1].SpinColorWave(-50,prideLesbian);
  systemLeds.virtualLedStrip[0].ScrollColorsOnFrontStrips(300,prideLesbian,1,0,1,0);
  systemLeds.virtualLedStrip[0].ScrollColorsOnFrontStrips(-300,prideTransgender,0,1,0,1);
  
  systemLeds.CopyAspectFanToExternalArray(0,aspect0Leds);
  systemLeds.CopyAspectFanToExternalArray(1,aspect1Leds);

  systemLeds.virtualLedStrip[0].CopyToExternalArray(stripLeds);


  //SerialPrintColor(aspect0Leds[0]);

  FastLED.show(); 
    
}