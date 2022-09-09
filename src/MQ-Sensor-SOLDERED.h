/**
 **************************************************
 *
 * @file        MQ-Sensor-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Zvonimir Haramustek for soldered.com
 ***************************************************/

#ifndef __MQ_SENSOR__
#define __MQ_SENSOR__

#include "Arduino.h"
#include "libs/MQUnifiedsensor/src/MQUnifiedsensor.h"

#ifdef __AVR__

#define VOLTAGE_RES 5
#define ADC_RES     10

#elif ESP32

#define VOLTAGE_RES 3.3
#define ADC_RES     12

#elif ESP8266

#define VOLTAGE_RES 3.3
#define ADC_RES     10
#endif

class MQ_Sensor : public MQUnifiedsensor
{
  public:
    MQ_Sensor(int _aPin, int _dPin, String type) : MQUnifiedsensor(_aPin, "Arduino", VOLTAGE_RES, ADC_RES, type)
    {
        if (_aPin == -1)
        {
            native = 0;
            setVoltResolution(5);
            setADC(10);
        }
        else
        {
            aPin = _aPin;
            dPin = _dPin;
        }
    }

    void begin(int _addr = 0x00);

    bool digitalRead();

  private:
    int aPin, dPin;
};

class MQ2 : public MQ_Sensor
{
  public:
    MQ2(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-2")
    {
    }
};

class MQ3 : public MQ_Sensor
{
  public:
    MQ3(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-3")
    {
    }
};

class MQ4 : public MQ_Sensor
{
  public:
    MQ4(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-4")
    {
    }
};

class MQ6 : public MQ_Sensor
{
  public:
    MQ6(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-6")
    {
    }
};

class MQ7 : public MQ_Sensor
{
  public:
    MQ7(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-7")
    {
    }
};

class MQ8 : public MQ_Sensor
{
  public:
    MQ8(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-8")
    {
    }
};

class MQ9 : public MQ_Sensor
{
  public:
    MQ9(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-9")
    {
    }
};

class MQ131 : public MQ_Sensor
{
  public:
    MQ131(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-131")
    {
    }
};

class MQ135 : public MQ_Sensor
{
  public:
    MQ135(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-135")
    {
    }
};

class MQ136 : public MQ_Sensor
{
  public:
    MQ136(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-136")
    {
    }
};

class MQ137 : public MQ_Sensor
{
  public:
    MQ137(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-137")
    {
    }
};

class MQ138 : public MQ_Sensor
{
  public:
    MQ138(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-138")
    {
    }
};

class MQ214 : public MQ_Sensor
{
  public:
    MQ214(int aPin = -1, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-214")
    {
    }
};

#endif
