// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// PCF8574
// This code is designed to work with the PCF8574_LBAR_I2CL I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <Wire.h>

// PCF8574 I2C address is 0x20(32)
#define Addr 0x20

void setup()
{
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select GPIO as input
  Wire.write(0xFF);
  // Stop I2C transmission
  Wire.endTransmission();

  // Output to serial monitor
  Serial.println("All Pins State are HIGH");
  delay(300);
}

void loop()
{
  unsigned int data;
  
  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Stop I2C transmission
  Wire.endTransmission();
    
  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  
  // Read 1 byte of data 
  if(Wire.available() == 1)
  {
    data = Wire.read();
  }

  // Convert the data
  data = data & 0xFF;
  
  for(int i = 0; i < 8;  i++)
  {
    if((data & ((unsigned int)pow(2, i))) == 0)
    {
      Serial.print("I/O Pin ");
      Serial.print(i);
      Serial.println(" State is LOW");
    }
    else
    {
      Serial.print("I/O Pin ");
      Serial.print(i);
      Serial.println(" State is HIGH");
    }
    delay(500);
  }
}

