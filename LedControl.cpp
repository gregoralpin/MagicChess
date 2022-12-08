#include <Arduino.h>
#include "LedControl.h"

void LEDControl::TurnLedOnOff(ledPos, bool onoff, int color){
  if(onoff == false){
    leds[ledPos] = CRGB::Black;
  }
}

void LEDControl::TurnLedsOn(int *ledList, int color){
  for (int i = 0; i < sizeof(ledList)/sizeof(ledList[0]); i++){
    if(ledList[i] != -1){
      int p = posConversor(i);
      leds[p] = color;
    }
  }
  FastLED.show();
}
void LEDControl::TurnEverythingOff(){
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    
  }
  FastLED.show();
}
