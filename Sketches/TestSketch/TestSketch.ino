#include "FastLed.h"
#define NUM_LEDS 30

CRGB leds[NUM_LEDS];

#define PIN 13

void setup()
{
  FastLed.addLeds<WS2812, PIN, RGB>(leds, NUM_LEDS);
}

void loop() 
{
  RGBLoop();
  Strobe(0xff, 0xff, 0xff, 10, 50, 1000);
  HalloweenEyes(0xff, 0x00, 0x00, 
                              1, 4, 
                              true, random(5,50), random(50,150), 
                              random(1000, 10000));
}

void RGBLoop(){
  for(int j = 0; j < 3; j++ ) { 
    for(int k = 0; k < 256; k++) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue);
    showStrip();
    delay(FlashDelay);
    setAll(0,0,0);
    showStrip();
    delay(FlashDelay);
  }
 
 delay(EndPause);
}

void HalloweenEyes(byte red, byte green, byte blue, 
                   int EyeWidth, int EyeSpace, 
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause){
  randomSeed(analogRead(0));
  
  int i;
  int StartPoint  = random( 0, NUM_LEDS - (2*EyeWidth) - EyeSpace );
  int Start2ndEye = StartPoint + EyeWidth + EyeSpace;
  
  for(i = 0; i < EyeWidth; i++) {
    setPixel(StartPoint + i, red, green, blue);
    setPixel(Start2ndEye + i, red, green, blue);
  }
  
  showStrip();
  
  if(Fade==true) {
    float r, g, b;
  
    for(int j = Steps; j >= 0; j--) {
      r = j*(red/Steps);
      g = j*(green/Steps);
      b = j*(blue/Steps);
      
      for(i = 0; i < EyeWidth; i++) {
        setPixel(StartPoint + i, r, g, b);
        setPixel(Start2ndEye + i, r, g, b);
      }
      
      showStrip();
      delay(FadeDelay);
    }
  }
  
  setAll(0,0,0); // Set all black
  
  delay(EndPause);
}
