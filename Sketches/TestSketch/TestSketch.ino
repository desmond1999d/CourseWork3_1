#include <FastLED.h> 

#define NUM_LEDS 38

CRGB leds[NUM_LEDS];

#define PIN 13
int max_bright = 200; 
int ledMode = 3;
int thissat = 255;
int index = 0;      
int ihue = 0;  

void one_color_all(int cred, int cgrn, int cblu) {   
  for (int i = 0 ; i < NUM_LEDS; i++ ) {
    leds[i].setRGB( cred, cgrn, cblu);
  }
}

void setup()
{
  Serial.begin(9600);
  LEDS.setBrightness(max_bright);
  LEDS.addLeds<WS2812, PIN, RGB>(leds, NUM_LEDS);
  one_color_all(0, 0, 0);          
  LEDS.show(); 
}

void set_color_led(int adex, int cred, int cgrn, int cblu) {
  leds[adex].setRGB( cred, cgrn, cblu);
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}

void RGBLoop(){
  for(int j = 0; j < 3; j++ ) { 
    for(int k = 0; k < 256; k++) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      FastLED.show();
      delay(3);
    }
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      FastLED.show();
      delay(3);
    }
  }
}

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause) {
  for (int j = 0; j < StrobeCount; j++) {
    setAll(red, green, blue);
    FastLED.show();
    delay(FlashDelay);
    setAll(0, 0, 0);
    FastLED.show();
    delay(FlashDelay);
  }

  delay(EndPause);
}

void rainbow_loop() {               
  index++;
  ihue = ihue + 10;
  if (index >= NUM_LEDS) {
    index = 0;
  }
  if (ihue > 255) {
    ihue = 0;
  }
  leds[index] = CHSV(ihue, thissat, 255);
  LEDS.show();
  delay(20);
}

void loop() 
{
  if(Serial.available() > 0) {
    ledMode = Serial.parseInt();
  }
  switch(ledMode) {
  case 0: break;
  case 1: RGBLoop(); break;
  case 2: Strobe(0x88, 0x11, 0x22, 10, 500, 1000); break;
  case 3: rainbow_loop(); break;
  }
}
