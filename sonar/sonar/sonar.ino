int duration;
double distance;

void setup(){
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
}

void loop(){
  digitalWrite(11,LOW);
  delayMicroseconds(5);
  digitalWrite(11, HIGH);
  delayMicroseconds(15);
  digitalWrite(11, LOW);
  delayMicroseconds(5);  
  duration = pulseIn(12, HIGH);
  distance = duration/58.2;
  Serial.println(distance);

  delay(50);
}
