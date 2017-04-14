#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 1

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 4
#define DELTA 1
#define UPPER 255 - DELTA
#define LOWER 0 + DELTA

#define PHOTO_IN_PIN 1
//#define SOUND_IN_PIN 3
#define PHOTO_OFF_THRESH 200
//#define PHOTO_OFF_THRESH 100 // test in light
//#define SOUND_THRESH 100
#define TIME_LIMIT 2400 // in cycles (4 cycles/second) = 600 seconds 

// Define the array of leds
CRGB leds[NUM_LEDS];
int hue = LOWER;
int cycles = 0;

void setup() {
  pinMode(PHOTO_IN_PIN, INPUT);
  //pinMode(SOUND_IN_PIN, INPUT);
  analogReference(DEFAULT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  
  FastLED.show();
}

void loop() {
  if(cycles > TIME_LIMIT)
  {
    for(int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
    }

    FastLED.show();
    return;
  }
  if(hue > UPPER)
  {
    hue = 0;
  }
  hue += DELTA;

  int brt = analogRead(PHOTO_IN_PIN) / 4; // convert 0-1023 to 0-255
  /*
  int snd = analogRead(SOUND_IN_PIN);
  if(snd > SOUND_THRESH)
  {
    hue = LOWER;
  }
  */
  if(brt < PHOTO_OFF_THRESH)
  {
    brt = 0;
  }
  
  for(byte i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(hue, 255, brt);
  }
  
  FastLED.show();
  delay(250);
  cycles++;
}
