#include<Servo.h>
Servo myServo;
const int servoControl = 9;

void setup(){
  Serial.begin(9600);
  myServo.attach(servoControl);
  myServo.write(0);
}

void loop(){
  myServo.write(359);
  delay(2000);
  myServo.write(0);
  delay(2000);
}
