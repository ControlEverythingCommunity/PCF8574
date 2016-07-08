# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# PCF8574
# This code is designed to work with the PCF8574_LBAR_I2CL I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# PCF8574 address, 0x20(32)
#		0xFF(255)	All pins configured as inputs
bus.write_byte(0x20, 0xFF)

time.sleep(0.5)

# PCF8574 address, 0x20(32)
# Read data back, 1 byte
data = bus.read_byte(0x20)


# Convert the data
data = (data & 0xFF)

for i in range(0, 8) :
    if (data & (2 ** i)) == 0 :
        print "I/O Pin %d State is LOW" %(i)
    else :
        print "I/O Pin %d State is HIGH" %(i)
        time.sleep(0.5)
