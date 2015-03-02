#include <SoftwareSerial.h>

char c;
SoftwareSerial BTSerial(10, 11);
void setup(){

  BTSerial.begin(9600);
  BTSerial.flush();
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop(){
  if (BTSerial.available()){
    c = BTSerial.read();
  }  
  if(c == '6')
    digitalWrite(6, HIGH);
  else if(c == '7')  
    digitalWrite(7, HIGH);
  else if(c == '8')
    digitalWrite(8, HIGH);
  else if(c == '9')
    digitalWrite(9, HIGH);
  else if(c == '0'){
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
}
