#include <Adafruit_NeoPixel.h>

#define PIN 2
#define LED_COUNT 450

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_RGB + NEO_KHZ800);

uint32_t green = 0xFF0000;
uint32_t red = 0x00FF00;
uint32_t blue = 0x0000FF;
uint32_t orange = 0xFFA300;
uint32_t yellow = 0xFFFF00;
uint32_t teal = 0xFF00FF;
uint32_t purple = 0x00FFFF;
uint32_t white = 0xFFFFFF;

void clearStrip() {
  for( int i = 0; i<LED_COUNT; i++){
    strip.setPixelColor(i, 0x000000); strip.show();
  }
}
 
void setup() {
  strip.begin();
  strip.show();
  
  Serial.begin(9600);
  
  clearStrip();
}

void loop() {
 
//for(uint16_t j=0; j<LED_COUNT; j++) {
//strip.setPixelColor(j, dimColor(orange,j+1));
//}
  
 strip.show();
//  delay(10);
//  colorWipe(strip.Color(255, 163, 0), 50);
//strip.setBrightness(30);
colourCycle(orange);
}


void colourCycle(uint32_t color){
  uint32_t old_val[LED_COUNT];
clearStrip();
  for(uint16_t i=0; i<LED_COUNT; i++) {
clearStrip();
      strip.setPixelColor(i, color); 
      for(int x = i; x<LED_COUNT; x++) {
        strip.setPixelColor(x, dimColor(orange,x+1)); 
          delay(150);
//        strip.show();
      }
      strip.show();
      delay(150);
  }
}

uint32_t dimColor(uint32_t color, uint8_t width) {
   return (((color&0xFF0000)/width)&0xFF0000) + (((color&0x00FF00)/width)&0x00FF00) + (((color&0x0000FF)/width)&0x0000FF);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}


void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
