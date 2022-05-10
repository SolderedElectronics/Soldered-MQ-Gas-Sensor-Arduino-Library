/*
  MQ6 Library - reading an mq6

  Demonstrates the use a mq6 sensor.
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

#define RatioMQ6CleanAir 10 // RS / R0 = 10 ppm

// Declare Sensor
MQ6 mq6(SENSOR_PIN); // If you have easyC version of this sensor
                     // just plug it in microcontroller and
                     // remove this "(SENSOR_PIN)" because sensor
                     // is not connected to pin but on I2C bus

void setup()
{
    // Init the serial port communication - to debug the library
    Serial.begin(115200); // Init serial port

    // Set math model to calculate the PPM concentration and the value of constants
    mq6.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq6.setA(2127.2);
    mq6.setB(-2.526); // Configurate the ecuation values to get CH4 concentration
    /*
      Exponential regression:
    GAS     | a      | b
    H2      | 88158  | -3.597
    LPG     | 1009.2 | -2.35
    CH4     | 2127.2 | -2.526
    CO      | 1000000000000000 | -13.5
    Alcohol | 50000000 | -6.017
    */

    /*****************************  MQ Init ********************************************/
    // Remarks: Configure the pin of arduino as input.
    /************************************************************************************/
    mq6.begin(); // If you have easyC version of this sensor
                 // you should add here I2C address of sensor
                 // which is 0x30 by default and can be changed
                 // by onboard switches labeled with ADDR
    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq6.setRL(10);
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
        mq6.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq6.calibrate(RatioMQ6CleanAir);
        Serial.print(".");
    }
    mq6.setR0(calcR0 / 10);
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
    mq6.serialDebug(true);
}

void loop()
{
    mq6.update();      // Update data, the arduino will be read the voltage on the analog pin
    mq6.readSensor();  // Sensor will read PPM concentration using the model and a and b values setted before or in the
                       // setup
    mq6.serialDebug(); // Will print the table on the serial port
    delay(500);        // Sampling frequency
}
