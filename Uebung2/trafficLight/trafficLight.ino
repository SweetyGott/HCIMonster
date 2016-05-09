#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN  6 // Echo Pin
#define trigPin 7 // Trigger Pin
#define echoPin 8 // Echo Pin
#define PIN_ECHO 8

#define NUM_PIXELS 12

int maximumRange = 20; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance


Adafruit_NeoPixel ring = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
  Serial.begin (9600);
  ring.begin();
  ring.show(); // Initialize all pixels to 'off'

  //Serial.begin(9600);
}
int inc = 0;
int color = 0;
void loop() {
   digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 Serial.println(distance);
 if (distance >= maximumRange || distance <= minimumRange){
 /* Send a negative number to computer and Turn LED ON 
 to indicate "out of range" */
 //Serial.println("-1");
  setRed();
 }
 else {
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. */
 Serial.println(distance);
  setGreen();
 }
 
 //Delay 50ms before next reading.
 delay(50);
}

void setGreen(){
  for (uint16_t px=0; px<NUM_PIXELS; px++){
    //setPixel(px,firstSensor/4,0,0);  
    setPixel(px,0,255,0);
  }
}

/*void setYellow(){
  for (uint16_t px=0; px<NUM_PIXELS; px++){
    //setPixel(px,firstSensor/4,0,0);  
    setPixel(px,0,255,255);
  }
}*/

void setRed(){
  for (uint16_t px=0; px<NUM_PIXELS; px++){
    //setPixel(px,firstSensor/4,0,0);  
    setPixel(px,255,0,0);
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

