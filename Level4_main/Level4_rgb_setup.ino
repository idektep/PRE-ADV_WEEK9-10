#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NEOPIXEL_PIN 8
#define NEOPIXEL_PIN2 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(12, NEOPIXEL_PIN2, NEO_GRB + NEO_KHZ800);
/*-----------------------------------------------*/
void NeopixelSetup()
{
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  strip2.begin();
  strip2.setBrightness(50);
  strip2.show(); // Initialize all pixels to 'off'
}
/*-----------------------------------------------*/
void Color(uint8_t r, uint8_t g, uint8_t b)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(r, g, b));
    strip2.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
  strip2.show();
}

/*-----------------------------------------------*/
void ColorWipe(uint32_t c, uint16_t Wait) 
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, c);
    strip2.setPixelColor(i, c);
    strip2.show();
    strip.show();
    delay(Wait);
  }
}
/*-----------------------------------------------*/
void Rainbow(uint16_t Wait) 
{
  uint16_t i = 0;
  uint16_t j = 0;
  for (j = 0; j < 256; j++) 
  {
    for (i = 0; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, Wheel((i + j) & 255));
      strip2.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    strip2.show();
    delay(Wait);
  }
}
/*-----------------------------------------------*/
// Slightly different, this makes the rainbow equally distributed throughout
void RainbowCycle(uint16_t Wait) 
{
  uint16_t i = 0;
  uint16_t j = 0;
  for (j = 0; j < 256 * 5; j++) 
  { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      strip2.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    strip2.show();
    delay(Wait);
  }
}
/*-----------------------------------------------*/
//Theatre-style crawling lights.
void TheaterChase(uint32_t c, uint16_t Wait) 
{
  for (int j = 0; j < 10; j++) 
  { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) 
    {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) 
      {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
        strip2.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();
      strip2.show();

      delay(Wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) 
      {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
        strip2.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}
/*-----------------------------------------------*/
//Theatre-style crawling lights with rainbow effect
void TheaterChaseRainbow(uint16_t Wait) 
{
  for (int j = 0; j < 256; j++) 
  {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) 
    {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) 
      {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
        strip2.setPixelColor(i + q, Wheel( (i + j) % 255));
      }
      strip.show();
      strip2.show();
      delay(Wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) 
      {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
        strip2.setPixelColor(i + q, 0);
      }
    }
  }
}
/*-----------------------------------------------*/
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) 
  {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) 
  {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
/*-----------------------------------------------*/
void NeopixelClose()
{
  strip.clear();
  strip2.clear();
  strip.show();
  strip2.show();
}
