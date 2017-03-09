#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 23

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 4
#define DELTA 1
#define UPPER 255 - DELTA
#define LOWER 0 + DELTA

#define ANALOG_IN_PIN 1
#define OFF_THRESH 100

// Define the array of leds
CRGB leds[NUM_LEDS];
int hue = LOWER;

void setup() {
  pinMode(ANALOG_IN_PIN, INPUT);
  analogReference(DEFAULT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  
  FastLED.show();
}

void loop() {
  if(hue > UPPER)
  {
    hue = 0;
  }
  hue += DELTA;

  // analogRead range is 0 - 1023. must adjust to be w/in 0 - 255
  /*
  int brt = 0;
  if(analogRead(ANALOG_IN_PIN) < 512)
  {
    brt = 255;
  } else {
    brt = 0;
  }
  */

  int brt = analogRead(ANALOG_IN_PIN) / 4;
  if(brt < OFF_THRESH)
  {
    brt = 0;
  }
  
  for(byte i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(hue, 255, brt);
  }
  
  FastLED.show();
  delay(150);
}
