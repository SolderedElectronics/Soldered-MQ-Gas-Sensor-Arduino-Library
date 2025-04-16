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
#include "sensorConfigData.h"

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
    MQ_Sensor(int _aPin, int _dPin, String type, sensorType sType) : MQUnifiedsensor(_aPin, "Arduino", VOLTAGE_RES, ADC_RES, type)
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
        sensor_type=sType;
    }

    void begin();
    void begin(sensorType configcustom);
    bool begin(int _addr);
    bool begin(int _addr, sensorType configcustom);
    void setRegressionModel(const sensorType& type);
    bool calibrateSensor(int numOfCalibrations);
    bool digitalRead();

  private:
    void setConfiguration(sensorType &type);
    int aPin, dPin;
    sensorType sensor_type;


};

class MQ2 : public MQ_Sensor
{
  public:
    MQ2(int aPin = -1, int dPin = -1, sensorType sType=MQ2_config ) : MQ_Sensor(aPin, dPin, "MQ-2", sType)
    {
    }
};

class MQ3 : public MQ_Sensor
{
  public:
    MQ3(int aPin = -1, int dPin = -1, sensorType sType=MQ3_config ) : MQ_Sensor(aPin, dPin, "MQ-3", sType)
    {
    }
};

class MQ4 : public MQ_Sensor
{
  public:
    MQ4(int aPin = -1, int dPin = -1, sensorType sType=MQ4_config ) : MQ_Sensor(aPin, dPin, "MQ-4", sType)
    {
    }
};


class MQ5 : public MQ_Sensor
{
  public:
    MQ5(int aPin = -1, int dPin = -1, sensorType sType=MQ5_config ) : MQ_Sensor(aPin, dPin, "MQ-5", sType)
    {
    }
};

class MQ6 : public MQ_Sensor
{
  public:
    MQ6(int aPin = -1, int dPin = -1, sensorType sType=MQ6_config ) : MQ_Sensor(aPin, dPin, "MQ-6", sType)
    {
    }
};

class MQ7 : public MQ_Sensor
{
  public:
    MQ7(int aPin = -1, int dPin = -1, sensorType sType=MQ7_config ) : MQ_Sensor(aPin, dPin, "MQ-7", sType)
    {
    }
};

class MQ8 : public MQ_Sensor
{
  public:
    MQ8(int aPin = -1, int dPin = -1, sensorType sType=MQ8_config ) : MQ_Sensor(aPin, dPin, "MQ-8", sType)
    {
    }
    private:
      sensorType sensor_type;
};

class MQ9 : public MQ_Sensor
{
  public:
    MQ9(int aPin = -1, int dPin = -1, sensorType sType=MQ9_config ) : MQ_Sensor(aPin, dPin, "MQ-9", sType)
    {
    }
};

class MQ131 : public MQ_Sensor
{
  public:
    MQ131(int aPin = -1, int dPin = -1, sensorType sType=MQ131_config ) : MQ_Sensor(aPin, dPin, "MQ-131", sType)
    {
    }
};

class MQ135 : public MQ_Sensor
{
  public:
    MQ135(int aPin = -1, int dPin = -1, sensorType sType=MQ135_config ) : MQ_Sensor(aPin, dPin, "MQ-135", sType)
    {
    }
};

class MQ136 : public MQ_Sensor
{
  public:
    MQ136(int aPin = -1, int dPin = -1, sensorType sType=Blank_config ) : MQ_Sensor(aPin, dPin, "MQ-136", sType)
    {
    }
};

class MQ137 : public MQ_Sensor
{
  public:
    MQ137(int aPin = -1, int dPin = -1, sensorType sType=MQ137_config ) : MQ_Sensor(aPin, dPin, "MQ-137", sType)
    {
    }
};

class MQ138 : public MQ_Sensor
{
  public:
    MQ138(int aPin = -1, int dPin = -1, sensorType sType=MQ138_config ) : MQ_Sensor(aPin, dPin, "MQ-138", sType)
    {
    }
};

class MQ214 : public MQ_Sensor
{
  public:
    MQ214(int aPin = -1, int dPin = -1, sensorType sType=Blank_config ) : MQ_Sensor(aPin, dPin, "MQ-214", sType)
    {
    }
};

#endif
