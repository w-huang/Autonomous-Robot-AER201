#include <Wire.h> //I2C Arduino Library

#define Addr 0x1E //0011110b, I2C 7bit address of HMC5883
int x,y,z; //triple axis data
float goodX, goodY, goodZ;
int xScale = 1;
int yScale = 1;
int xShift = 0;
int yShift = 0;
double comAngle;
void setup(){
  //Initialize Serial and I2C communications
  Serial.begin(9600);
  delay(100);
  Wire.begin();
  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(Addr); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}


void loop(){
  
  //Tell the HMC5883L where to begin reading data
  Wire.beginTransmission(Addr);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(Addr, 6);
  if(6>=Wire.available()){
    x = Wire.read(); 
    z = Wire.read();
    y = Wire.read();
  }
  
  Serial.print("X: ");
  Serial.print(x);
  Serial.print("  Y: ");
  Serial.print(y);
  Serial.print("  Z: ");
  Serial.print(z);
  Serial.print("\n");
  
/*  goodX = (float)x * xScale + (float) xShift;
  goodY = (float)y * yScale + (float) yShift;
  
  comAngle = atan2(goodY, goodX)/ 3.1415926 * 180;
  if (comAngle < 0)
    comAngle += 360;
  Serial.println(comAngle);
*/  delay(250);
};
