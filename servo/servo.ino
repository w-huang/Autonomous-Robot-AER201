#include<Servo.h>
Servo myServo;
const int compass = A0;
const int servoControl = 9;
int potVal;
int angle;

void setup(){
  Serial.begin(9600);
  myServo.attach(servoControl);
}

void loop(){
  potVal = analogRead(compass);
  Serial.print("compass reading: ");
  Serial.print(potVal);
  angle = map(potVal, 0, 1023, 0, 179);
  Serial.print("\t Angle: ");
  Serial.print(angle);
  Serial.print("\n");
  myServo.write(angle);
  delay(15);
}
