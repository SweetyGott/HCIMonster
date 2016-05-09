/*
  Serial Call and Response in ASCII
 Language: Wiring/Arduino

 This program sends an ASCII A (byte of value 65) on startup
 and repeats that until it gets some data in.
 Then it waits for a byte in the serial port, and
 sends three ASCII-encoded, comma-separated sensor values,
 truncated by a linefeed and carriage return,
 whenever it gets a byte in.

 Thanks to Greg Shakar and Scott Fitzgerald for the improvements

  The circuit:
 * potentiometers attached to analog inputs 0 and 1
 * pushbutton attached to digital I/O 2



 Created 26 Sept. 2005
 by Tom Igoe
 modified 24 Apr 2012
 by Tom Igoe and Scott Fitzgerald

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialCallResponseASCII

 */

int firstSensor = 0;    // first analog sensor
float val=0;

int red = 3;
int green = 5;
int blue = 6;

int MAX = 631;
int step = 90;
void setup() {
  Serial.begin(9600);
  
  pinMode(red, OUTPUT);  
  pinMode(green, OUTPUT);  
  pinMode(blue, OUTPUT);  
}

void loop() {
    step = MAX / 7;
    
    firstSensor = analogRead(A0);
    if (firstSensor < 1*step)
      color(255,0,0);
    else if(firstSensor<2*step)
      color(255,127,0);    
    else if(firstSensor<3*step)
      color(255,255,0); 
    else if(firstSensor<4*step)
      color(0,255,0); 
    else if(firstSensor<5*step)
      color(0,255,255);
    else if(firstSensor<6*step)
      color(0,0,255); 
    else if(firstSensor<7*step)
      color(255,0,255); 
    
    
    
    Serial.println(firstSensor);
}


void color(int r, int g, int b){
  analogWrite(red, r*3);
  analogWrite(green, g*3);
  analogWrite(blue, b*3);
}

