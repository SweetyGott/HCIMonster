#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

#define NUM_PIXELS 12


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
  int in = analogRead(A0);
  int a = (in >> 2) & 0xe0;
  int b = (in << 1) & 0x78;
  int c = (in << 5) & 0xe0;
  //Serial.println(in);
  for (uint16_t px=0; px<NUM_PIXELS; px++){
    //setPixel(px,firstSensor/4,0,0);  
    setPixel(px,a,b,c);
    delay(50);
    setPixel(px,0,0,0);  
  }
  
}

void setPixel(uint16_t pixel, char r, char g, char b){
  uint32_t color = ring.Color(r, g, b);
  ring.setPixelColor(pixel, color);
  ring.show();
}

void setPixelC(uint16_t pixel, uint32_t color){
  ring.setPixelColor(pixel, color);
  ring.show();
}

