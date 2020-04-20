#include <IRremote.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define RECV_PIN 11  // Infrared Reciever Pin
#define NEOPIN 6     // define Neopixel pin D6
#define NUMPIX 2     // define Number of pixels

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIX, NEOPIN, NEO_GRB + NEO_KHZ800);
IRrecv irrecv(RECV_PIN);
decode_results results;
int brightness = 255;

void setup() {
  irrecv.enableIRIn();
  pixels.begin();
  pixels.setBrightness(255);
  pixels.show();
}

void loop() {
  if (irrecv.decode(&results)) {
    switch(results.value) {
      case 0x11D1245B:   //INCREASE BRIGHTNESS
              if (brightness <= 254) {
                brightness = brightness + 10;
              }
              for(int i=0;i<NUMPIX;i++) {
                pixels.setPixelColor(i, brightness, brightness, brightness);
              }
              pixels.show();
              break;

          case 0x2AEF9F6B:   //DECREASE BRIGHTNESS
              if (brightness > 15) {
                brightness = brightness - 10;
              }
              for(int i=0;i<NUMPIX;i++) {
                pixels.setPixelColor(i, brightness, brightness, brightness);
              }
              pixels.show();
              break;

          case 0x3C394F3F:   //RED BUTTON
              for(int i=0;i<NUMPIX;i++) {
                pixels.setPixelColor(i, brightness, 0, 0);
              }
              pixels.show();
              break;

          case 0X9BBEEE1B:   //GREEN BUTTON
              for(int i=0;i<NUMPIX;i++) {
                pixels.setPixelColor(i, 0, brightness, 0);
              }
              pixels.show();
              break;

          case 0x572D786B:   //BLUE BUTTON
              for(int i=0;i<NUMPIX;i++) {
                pixels.setPixelColor(i, 0, 0, brightness);
              }
              pixels.show();
              break;

          case 0xD63F6BDF:   //YELLOW BUTTON
              for(int i=0;i<NUMPIX;i++) {
                pixels.setPixelColor(i, brightness, brightness, 0);
              }
              pixels.show();
              break;

          case 0xDAA32421:   //OFF BUTTON
              for(int i=0;i<NUMPIX;i++) {
                pixels.setPixelColor(i, 0, 0, 0);
              }
              pixels.show();
              break;

          case 0x6B15BC83:  //PLAY BUTTON
              for(int i=0;i<NUMPIX;i++) {
                while (true) {
                  rainbow(115);
                }
              }
              pixels.show();
              break;
    }
    irrecv.resume();
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
