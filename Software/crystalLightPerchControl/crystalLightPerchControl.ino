#include "FastLED.h"

#define NUM_LEDS 1
#define DATA_PIN 4
#define DELAY 1000
#define LIMIT 768
#define LIGHT_IN_PIN 1 // apparently...
#define SOUND_IN_PIN PB3

// Define the array of leds
CRGB leds[NUM_LEDS];

void setColor(CRGB color) {
  for(unsigned char i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
}

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  setColor(CRGB::Black);
  FastLED.show();
  delay(DELAY);
  
  setColor(CRGB::White);
  FastLED.show();
  delay(DELAY);
  
  setColor(CRGB::Black);
  FastLED.show();
  delay(DELAY);

  pinMode(SOUND_IN_PIN, INPUT);
  pinMode(LIGHT_IN_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(analogRead(LIGHT_IN_PIN) >= LIMIT) {
    if(analogRead(SOUND_IN_PIN) >= LIMIT) {
      setColor(CRGB::Green);
    } else {
      setColor(CRGB::Red);
    }
  } else {
    setColor(CRGB::Blue);
  }

  FastLED.show();
  delay(DELAY);
}
