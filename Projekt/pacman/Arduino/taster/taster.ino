#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define NUM_PIXELS 12
Adafruit_NeoPixel ring = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);


const int leftButton = 2;
const int upButton = 3;
const int rightButton = 4;
const int downButton = 5;
const int ledPin =  13;
int buttonState = 0;
#define CDS_INPUT 0 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(leftButton, INPUT);
  pinMode(upButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(downButton, INPUT);
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  ring.begin();
  ring.show(); // Initialize all pixels to 'off'
}
 
void loop(){
  String inputString;
  char buf[20];
  bool read = false;
  if (Serial.available()) {
    read = true;
    Serial.readBytes(buf,20);
    for(int i = 0; i < 20; ++i){
      inputString += (char) buf[i];  
    }
    for(int i = 0; i < NUM_PIXELS; ++i){
      if(i == buf[0])
        setPixel(i,255,0,0);
      else
        setPixel(i,0,0,0); 
    }
    Serial.println(buf[0]);
    //Serial.println(inputString); 
  }
  
  
    
  int left = digitalRead(leftButton);
  int up = digitalRead(upButton);
  int right = digitalRead(rightButton);
  int down = digitalRead(downButton);
  int value = 0;
  if(left == HIGH)
    value = 37;
  if(up == HIGH)
    value = 38;
  if(right == HIGH)
    value = 39;
  if(down == HIGH)
    value = 40;
  Serial.println(value); 
  if (value == HIGH) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
  //delay(100);
}

void setPixel(uint16_t pixel, char r, char g, char b){
  uint32_t color = ring.Color(r, g, b);
  ring.setPixelColor(pixel, color);
  ring.show();
}
