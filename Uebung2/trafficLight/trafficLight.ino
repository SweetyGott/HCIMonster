#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define echoPin 8 // Echo Pin
#define trigPin 7 // Trigger Pin
#define PIN_ECHO 8

#define NUM_PIXELS 12

int maximumRange = 5; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance


Adafruit_NeoPixel ring = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  pinMode(PIN_TRIGGER,OUTPUT);
  pinMode(PIN_ECHO,INPUT);
  Serial.begin (9600);
  ring.begin();
  ring.show(); // Initialize all pixels to 'off'

  //Serial.begin(9600);
}
int inc = 0;
int color = 0;
void loop() {
  digitalWrite(PIN_TRIGGER,LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);
  Serial.println(digitalRead(PIN_ECHO));
  //duration = pulseIn(PIN_ECHO, HIGH);
  Serial.println(duration);
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
  if (distance >= maximumRange || distance <= minimumRange){
    setRed();
    
   }
   else {
     setGreen();
   }
   
  delay(50);
  /*
  //Serial.println(in);
  if(color ==1){
    setGreen();
  }else if(color == 2){
    setYellow();
  }else{
    setRed();
  }
  inc++;
  inc %= 50;
  if(inc == 0){
    color= (color+1)%3;
  }
  */
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

