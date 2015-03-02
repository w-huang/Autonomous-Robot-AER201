
#include <Wire.h> //I2C Arduino Library

#define address 0x1E //0011110b, I2C 7bit address of HMC5883
float goodX;
float goodY;
float xScale = 1.3;
float yScale = 1;
float xShift = 0;
float yShift = 0;
float comShift = 0;

void setup(){
  //Initialize Serial and I2C communications
  Serial.begin(9600);
  Wire.begin();
  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

void loop(){
  
  int x,y,z; //triple axis data

  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
  
  goodX = (float)x * xScale + (float) xShift;
  goodY = (float)y * yScale + (float) yShift;
  
  float comAngle = atan2(goodY, goodX)/ 3.1415926 * 180;
  comAngle -= comShift;
  if (comAngle < 0)
    comAngle += 360;
  Serial.println(comAngle);
  
  delay(250);
}
