# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# PCF8574
# This code is designed to work with the PCF8574_LBAR_I2CL I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# PCF8574 address, 0x20(32)
#		0xFF(255)	All pins configured as inputs
data = [0xFF]
i2c.write(0x20, data)

time.sleep(0.5)

# PCF8574 address, 0x20(32)
# Read data back, 1 byte
data = i2c.readBytes(0x20, 0x00, 1)


# Convert the data
data[0] = (data[0] & 0xFF)

for i in range(0, 8) :
    if (data[0] & (2 ** i)) == 0 :
        print "I/O Pin %d State is LOW" %(i)
    else :
        print "I/O Pin %d State is HIGH" %(i)
        time.sleep(0.5)
