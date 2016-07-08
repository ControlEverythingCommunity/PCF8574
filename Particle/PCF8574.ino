// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// PCF8574
// This code is designed to work with the PCF8574_LBAR_I2CL I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>
#include <math.h>

// PCF8574 I2C address is 0x20(32)
#define Addr 0x20

int data = 0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "PCF8574");
  
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

  // Output to dashboard
  Particle.publish("All Pins State are ","HIGH");
  delay(1000);
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
      Particle.publish("I/O Pin ", String(i) + " State is LOW");
    }
    else
    {
      Particle.publish("I/O Pin ", String(i) + " State is HIGH");
    }
    delay(1000);
  }
}

