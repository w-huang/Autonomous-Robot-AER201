/*
HMC5883L.h - Header file for the HMC5883L Triple Axis Magnetometer Arduino Library.
Copyright (C) 2011 Love Electronics (loveelectronics.co.uk) / 2012 bildr.org (Arduino 1.0 compatible)

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

WARNING: THE HMC5883L IS NOT IDENTICAL TO THE HMC5883!
Datasheet for HMC5883L:
http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/HMC5883L_3-Axis_Digital_Compass_IC.pdf

*/

#include <Wire.h>

#ifndef HMC5883L_h
#define HMC5883L_h

#include <Arduino.h>
#include <Wire.h>



#define HMC5883L_Address 0x1E
#define ConfigurationRegisterA 0x00
#define ConfigurationRegisterB 0x01
#define ModeRegister 0x02
#define DataRegisterBegin 0x03

#define Measurement_Continuous 0x00
#define Measurement_SingleShot 0x01
#define Measurement_Idle 0x03

#define ErrorCode_1 "Entered scale was not valid, valid gauss values are: 0.88, 1.3, 1.9, 2.5, 4.0, 4.7, 5.6, 8.1"
#define ErrorCode_1_Num 1

struct MagnetometerScaled
{
    float XAxis;
    float YAxis;
    float ZAxis;
};

struct MagnetometerRaw
{
    int XAxis;
    int YAxis;
    int ZAxis;
};

class HMC5883L
{
    public:
     HMC5883L();

     MagnetometerRaw ReadRawAxis();
     MagnetometerScaled ReadScaledAxis();
 
     int SetMeasurementMode(uint8_t mode);
     int SetScale(float gauss);

     char* GetErrorText(int errorCode);

    protected:
     void Write(int address, int byte);
     uint8_t* Read(int address, int length);

    private:
     float m_Scale;
};
#endif

/*
HMC5883L.cpp - Class file for the HMC5883L Triple Axis Magnetometer Arduino Library.
Copyright (C) 2011 Love Electronics (loveelectronics.co.uk)/ 2012 bildr.org (Arduino 1.0 compatible)

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

WARNING: THE HMC5883L IS NOT IDENTICAL TO THE HMC5883!
Datasheet for HMC5883L:
http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/HMC5883L_3-Axis_Digital_Compass_IC.pdf

*/

#include <Arduino.h> 

HMC5883L::HMC5883L()
{
 m_Scale = 1;
}

MagnetometerRaw HMC5883L::ReadRawAxis()
{
 uint8_t* buffer = Read(DataRegisterBegin, 6);
 MagnetometerRaw raw = MagnetometerRaw();
 raw.XAxis = (buffer[0] << 8) | buffer[1];
 raw.ZAxis = (buffer[2] << 8) | buffer[3];
 raw.YAxis = (buffer[4] << 8) | buffer[5];
 return raw;
}

MagnetometerScaled HMC5883L::ReadScaledAxis()
{
 MagnetometerRaw raw = ReadRawAxis();
 MagnetometerScaled scaled = MagnetometerScaled();
 scaled.XAxis = raw.XAxis * m_Scale;
 scaled.ZAxis = raw.ZAxis * m_Scale;
 scaled.YAxis = raw.YAxis * m_Scale;
 return scaled;
}

int HMC5883L::SetScale(float gauss)
{
    uint8_t regValue = 0x00;
    if(gauss == 0.88)
    {
        regValue = 0x00;
        m_Scale = 0.73;
    }
    else if(gauss == 1.3)
    {
        regValue = 0x01;
        m_Scale = 0.92;
    }
    else if(gauss == 1.9)
    {
        regValue = 0x02;
        m_Scale = 1.22;
    }
    else if(gauss == 2.5)
    {
        regValue = 0x03;
        m_Scale = 1.52;
    }
    else if(gauss == 4.0)
    {
        regValue = 0x04;
        m_Scale = 2.27;
    }
    else if(gauss == 4.7)
    {
        regValue = 0x05;
        m_Scale = 2.56;
    }
    else if(gauss == 5.6)
    {
        regValue = 0x06;
        m_Scale = 3.03;
    }
    else if(gauss == 8.1)
    {
        regValue = 0x07;
        m_Scale = 4.35;
    }
    else
        return ErrorCode_1_Num;
    
    // Setting is in the top 3 bits of the register.
    regValue = regValue << 5;
    Write(ConfigurationRegisterB, regValue);
}

int HMC5883L::SetMeasurementMode(uint8_t mode)
{
    Write(ModeRegister, mode);
}

void HMC5883L::Write(int address, int data)
{
 Wire.beginTransmission(HMC5883L_Address);
 Wire.write(address);
 Wire.write(data);
 Wire.endTransmission();
}

uint8_t* HMC5883L::Read(int address, int length)
{
 Wire.beginTransmission(HMC5883L_Address);
 Wire.write(address);
 Wire.endTransmission();
 
 Wire.beginTransmission(HMC5883L_Address);
 Wire.requestFrom(HMC5883L_Address, length);

 uint8_t buffer[length];
 if(Wire.available() == length)
 {
     for(uint8_t i = 0; i < length; i++)
     {
         buffer[i] = Wire.read();
     }
 }
 Wire.endTransmission();

 return buffer;
}

char* HMC5883L::GetErrorText(int errorCode)
{
    if(ErrorCode_1_Num == 1)
        return ErrorCode_1;
    
    return "Error not defined.";
}


HMC5883L compass;


void setup(){
 Serial.begin(9600);
 Wire.begin();
 
 compass = HMC5883L(); //new instance of HMC5883L library
 setupHMC5883L(); //setup the HMC5883L
}

// Our main program loop.
void loop(){
 
 float heading = getHeading();
 Serial.println(heading);
 delay(100); //only here to slow down the serial print

}

void setupHMC5883L(){
 //Setup the HMC5883L, and check for errors
 int error; 
 error = compass.SetScale(1.3); //Set the scale of the compass.
 if(error != 0) Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so

 error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
 if(error != 0) Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so
}

float getHeading(){
 //Get the reading from the HMC5883L and calculate the heading
 MagnetometerScaled scaled = compass.ReadScaledAxis(); //scaled values from compass.
 float heading = atan2(scaled.YAxis, scaled.XAxis);

 // Correct for when signs are reversed.
 if(heading < 0) heading += 2*PI;
 if(heading > 2*PI) heading -= 2*PI;

 return heading * RAD_TO_DEG; //radians to degrees
}
