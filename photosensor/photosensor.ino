const int redPin = 11;
const int greenPin = 9;
const int bluePin = 10;

const int redSensor = A0;
const int greenSensor = A1;
const int blueSensor = A2;

int redValue = 0;
int greenValue=0;
int blueValue=0;

int redReading = 0;
int greenReading = 0;
int blueReading = 0;


void setup(){
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop(){
  redReading = analogRead(redSensor);
  delay(5);
  greenReading = analogRead(greenSensor);
  delay(5);
  blueReading = analogRead(blueSensor);
  Serial.print("Raw Sensor Values RGB: ");
  Serial.print(redReading);
  Serial.print(" ");
  Serial.print(greenReading);
  Serial.print(" ");
  Serial.print(blueReading);
  Serial.print("\n");
  
  redValue = redSensor/4;
  greenValue = greenSensor/4;
  blueValue = blueSensor/4;
  
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
