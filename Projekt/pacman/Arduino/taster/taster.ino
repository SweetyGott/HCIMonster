// by DojoDave and Tom Igoe
 
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
}
 
void loop(){
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
  delay(100);
}
