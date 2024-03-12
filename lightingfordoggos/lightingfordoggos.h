#ifndef LIGHTINGFORDOGGOS_H
#define LIGHTINGFORDOGGOS_H

#include <Arduino.h>
#include <FastLED.h>

// old functions
int ConvertToPercentageOf255(int part, int whole);

// utility functions
void PrintAspectFanState(int deviceNumber);
void PrintFunctionDebugData(char funcName[], int timingSlot, int speed, bool timeSlot, bool color, bool accMillis, int device = 100);
void SerialPrintColor(CRGB color);
void SerialPrintVars(int var0 = 0, int var1 = 0, int var2 = 0, int var3 = 0, int var4 = 0);
CRGB CheckForRandomColor(int speed, int timingSlot, const int FRAMELIMIT, CRGB color);
void FrameAdvance(int speed, int timingSlot, int FRAMELIMIT);
bool TimingDrawAddCheck (int speed, int timingSlot);

// color functions
CRGB MakeRandomColor();

//single fan functions
void FanNewtonsCradle(int speed, int timingSlot, int device, CRGB color);
void FanSpin(int speed, int timingSlot, int device, CRGB color, CRGB color2 = CRGB::Black, CRGB color3 = CRGB::Black, int startFrame = 0);
void FanSpinColorWave(int speed, int timingSlot, int device);
void FanSpinFill(int speed, int timingSlot, int device, CRGB color);
void FanSpinFillEmpty(int speed, int timingSlot, int device, CRGB color, int reverseEmpty = 0);
void FanVertMovingLine(int speed, int timingSlot, int device, CRGB color, int startFrame = 0);
void FrontFanAlternateLoop(int speed, int timingSlot, CRGB color0, CRGB color1);
void FrontFansBlank();
void FrontFansVertBounce(int speed, int timingSlot, CRGB color, int startFrame = 0);
void StripRandomFlashing(int speed, int timingSlot, CRGB color);
void TransColorsScrollingFrontLeds(int speed, int timingSlot, CRGB color0, CRGB color1, CRGB color2, int side = 0);

#endif