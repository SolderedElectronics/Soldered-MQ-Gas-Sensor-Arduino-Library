/**
 **************************************************
 *
 * @file        Template for attiny_firmware
 * @brief       Fill in sensor specific code.
 *

 *
 * @authors     @ soldered.com
 ***************************************************/

#include "easyC.h"
#include <Wire.h>

int lastEvent=0;

int addr = DEFAULT_ADDRESS;
uint16_t d=0;
void setup()
{
    initDefault();
    addr = getI2CAddress();

    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop()
{
 
}

void receiveEvent(int howMany)
{
    while (1 < Wire.available())
    {
        char c = Wire.read();
    }

    char c = Wire.read();
}

void requestEvent()
{
    char a[2];
    d = analogRead(PA5);
    if (lastEvent==0)
    {
      a[0] = d & 0xFF;
      a[1] = (d >> 8) & 0xFF;     
      Wire.write(a, 2);
    }
}
