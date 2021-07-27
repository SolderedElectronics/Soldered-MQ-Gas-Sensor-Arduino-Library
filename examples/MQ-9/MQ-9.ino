/*
  MQUnifiedsensor Library - reading an mq9

  Demonstrates the use a mq9 sensor.
  Library originally added 01 may 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez

  Added example
  modified 23 May 2019
  by Miguel Califa

  Updated library usage
  modified 26 March 2020
  by Miguel Califa

  Wiring:
  https://github.com/miguel5612/MQSensorsLib_Docs/blob/master/static/img/MQ_Arduino.PNG


 This example code is in the public domain.

*/

// Include the library
#include "MQ-Sensor-SOLDERED.h"

// You can change the values of the variables below to pin you're using
#ifdef __AVR__
#define SENSOR_PIN A1
#else
#define SENSOR_PIN 5
#endif

#define RatioMQ9CleanAir (9.6) // RS / R0 = 60 ppm

MQ9 mq9(SENSOR_PIN); // pin A1

void setup()
{
    // Init the serial port communication - to debug the library
    Serial.begin(115200); // Init serial port

    // Set math model to calculate the PPM concentration and the value of constants
    mq9.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq9.setA(1000.5);
    mq9.setB(-2.186); // Configurate the ecuation values to get LPG concentration

    /*
      Exponential regression:
    GAS     | a      | b
    LPG     | 1000.5 | -2.186
    CH4     | 4269.6 | -2.648
    CO      | 599.65 | -2.244
    */

    /*****************************  MQ Init ********************************************/
    // Remarks: Configure the pin of arduino as input.
    /************************************************************************************/
    mq9.begin();
    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq9.setRL(10);
    */
    /*****************************  MQ CAlibration ********************************************/
    // Explanation:
    // In this routine the sensor will measure the resistance of the sensor supposing before was pre-heated
    // and now is on clean air (Calibration conditions), and it will setup R0 value.
    // We recomend execute this routine only on setup or on the laboratory and save on the eeprom of your arduino
    // This routine not need to execute to every restart, you can load your R0 if you know the value
    // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor
    Serial.print("Calibrating please wait.");
    float calcR0 = 0;
    for (int i = 1; i <= 10; i++)
    {
        mq9.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq9.calibrate(RatioMQ9CleanAir);
        Serial.print(".");
    }
    mq9.setR0(calcR0 / 10);
    Serial.println("  done!.");

    if (isinf(calcR0))
    {
        Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your "
                       "wiring and supply");
        while (1)
            ;
    }
    if (calcR0 == 0)
    {
        Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please "
                       "check your wiring and supply");
        while (1)
            ;
    }
    /*****************************  MQ CAlibration ********************************************/
    mq9.serialDebug(true);
}

void loop()
{
    mq9.update();      // Update data, the arduino will be read the voltage on the analog pin
    mq9.readSensor();  // Sensor will read PPM concentration using the model and a and b values setted before or in the
                       // setup
    mq9.serialDebug(); // Will print the table on the serial port
    delay(500);        // Sampling frequency
}