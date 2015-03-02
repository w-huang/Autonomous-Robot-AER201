#include<Servo.h>

Servo myServo;
const int servoControlPin = 9;
const int IRSensorPin = A0;
int IRValue = 0;

int motorControlPins[6] = {4,5,32,33,30,31}; //4, 5 for enables, 4 is left; 30-33 for HIGH/LOW, 30,31 is left.

void moveGate(Servo* myServo, int state){
  //takes a servo pointer and an int that specifies whether to open (1) or close (0);
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

void driveBack(){
  analogWrite(motorControlPins[0], 255);
  analogWrite(motorControlPins[1], 255);
  digitalWrite(motorControlPins[2], LOW);
  digitalWrite(motorControlPins[3], HIGH);
  digitalWrite(motorControlPins[4], LOW);
  digitalWrite(motorControlPins[5], HIGH);
  return;
}

void stop(){
  digitalWrite(motorControlPins[2], LOW);
  digitalWrite(motorControlPins[3], LOW);
  digitalWrite(motorControlPins[4], LOW);
  digitalWrite(motorControlPins[5], LOW);
}

int readIrSensor(int sensorPin){
  //returns the reading of an IR sensor from the pin specified.
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
  if (IRValue = readIrSensor(IRSensorPin) < 940){//change 940 to adjust closeness/farness of ball detection; IR has a logarithmic scale
    delay(1500);//delay between seeing ball and closing gate
    moveGate(&myServo, 0); //closes gate
    delay(10000);//delay after closing gate
    driveBack();//drives backward
    delay(3000);//how long to drive backward for
    stop();//stops locomotion
  }
  delay(50);
}

