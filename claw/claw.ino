#include<Servo.h>

Servo myServo;
const int servoControlPin = 9;
const int IRSensorPin = A0;
int IRValue = 0;

void moveGate(Servo* myServo, int state){
  //state = 1 for open, 0 for close
  if (state){
    Serial.println("openning gate");
    (*myServo).write(0);
    return;
  }
  (*myServo).write(90);
  Serial.println("closing gate");
  return;
}

int readIrSensor(int sensorPin){
  int value = analogRead(sensorPin);
  Serial.println(value);
  return value;
}

void setup(){
  Serial.begin(9600);
  myServo.attach(servoControlPin);
  myServo.write(0);
}


void loop(){
  if (IRValue = readIrSensor(IRSensorPin) < 940){
    moveGate(&myServo, 0);
    delay(10000);
    moveGate(&myServo,1);
    delay(4000);
  }
  delay(50);
}

