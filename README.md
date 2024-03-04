# Home_PC_arduino_LED_code
 code for running effects on aRGB LEDs in my desktop PC


**Current sub-project is converting to object-oriented code to avoid having to use global state-tracking arrays. This is mostly because
I can't figure out a good way to dynamically assign index numbers for state-tracking arrays when calling effects functions.
	This probabaly doesn't make any sense out of context.

This is code written for an Arduino to control aRGB LEDs.
The FastLED library provides the connection to the hardware, as well as a CRGB data-type and is required for this code to work.

This probably won't be immediately useful to anyone whose hardware isn't exactly the same as mine. 
I also have nearly no coding experience, so it's pretty rough at this point.
But I thought I'd share it for the couple of people who might be interested, and on the off chance it might 
actually be useful to someone trying to figure this stuff out.