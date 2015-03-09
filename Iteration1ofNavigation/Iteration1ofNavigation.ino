int motorControlPins[6] = {4,5,32,33,30,31}; //4, 5 for enables, 4 is left; 30-33 for HIGH/LOW, 30,31 is left.

void setup(){
  Serial.begin(9600);
  for (int i = 0; i < 6; ++i)
    pinMode(motorControlPins[i], OUTPUT);
}

void loop(){
  Serial.println("driving");
  analogWrite(motorControlPins[0], 255);
  analogWrite(motorControlPins[1], 255);
  digitalWrite(motorControlPins[2], HIGH);
  digitalWrite(motorControlPins[3], LOW);
  digitalWrite(motorControlPins[4], HIGH);
  digitalWrite(motorControlPins[5], LOW);
  delay(2500);
  Serial.println("turning");
  digitalWrite(motorControlPins[4], LOW);
  digitalWrite(motorControlPins[5], HIGH);
  delay(850);
}
