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
#define ADC_RES     10

#elif ESP8266

#define VOLTAGE_RES 3.3
#define ADC_RES     10
#endif

class MQ_Sensor : public MQUnifiedsensor
{
  public:
    MQ_Sensor(int _aPin, int _dPin, String type) : MQUnifiedsensor("Arduino", VOLTAGE_RES, ADC_RES, aPin, type)
    {
        aPin = _aPin;
        dPin = _dPin;
    }

    void begin();

    bool digitalRead();

  private:
    int aPin, dPin;
};

class MQ2 : public MQ_Sensor
{
  public:
    MQ2(int aPin, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-2")
    {
    }
};

class MQ3 : public MQ_Sensor
{
  public:
    MQ3(int aPin, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-3")
    {
    }
};

class MQ4 : public MQ_Sensor
{
  public:
    MQ4(int aPin, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-4")
    {
    }
};

class MQ6 : public MQ_Sensor
{
  public:
    MQ6(int aPin, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-6")
    {
    }
};

class MQ7 : public MQ_Sensor
{
  public:
    MQ7(int aPin, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-7")
    {
    }
};

class MQ8 : public MQ_Sensor
{
  public:
    MQ8(int aPin, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-8")
    {
    }
};

class MQ9 : public MQ_Sensor
{
  public:
    MQ9(int aPin, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-9")
    {
    }
};

class MQ135 : public MQ_Sensor
{
  public:
    MQ135(int aPin, int dPin = -1) : MQ_Sensor(aPin, dPin, "MQ-135")
    {
    }
};

#endif
