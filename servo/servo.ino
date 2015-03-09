#include<Servo.h>
Servo myServo;
const int servoControl = 8;

void setup(){
  Serial.begin(9600);
  myServo.attach(servoControl);
  myServo.write(0);
  Serial.println("15");
}

void loop(){
  myServo.write(330); Serial.println("340");
  delay(8000);
  myServo.write(15);  Serial.println("1`  5");
  delay(5000);
}
