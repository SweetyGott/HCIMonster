#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

#define NUM_PIXELS 12

#define PULSEMAX 5012
#define PULSEMIN 28



Adafruit_NeoPixel ring = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  ring.begin();
  ring.show(); // Initialize all pixels to 'off'

  //Serial.begin(9600);
}

void loop() {
  int value = 2106;
  int npx = NUM_PIXELS / (PULSEMAX*1.0) * value +1;
  setRed(npx);
}

void setRed(uint16_t n){
  for (uint16_t px=0; px<min(n,NUM_PIXELS); px++){
    setPixel(px,255,0,0);
  }
}

void setPixel(uint16_t pixel, char r, char g, char b){
  uint32_t color = ring.Color(r, g, b);
  ring.setPixelColor(pixel, color);
  ring.show();
}


