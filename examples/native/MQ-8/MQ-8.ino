/*
  MQUnifiedsensor Library - reading an mq8

  Demonstrates the use a mq8 sensor.
  Library originally added 01 may 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez

  Added example
  modified 23 May 2019
  by Miguel Califa

  Updated library usage
  modified 26 March 2020
  by Miguel Califa

  Example is modified by Soldered.com

  Wiring:
  https://github.com/miguel5612/MQSensorsLib_Docs/blob/master/static/img/MQ_Arduino.PNG


 This example code is in the public domain.

*/

// Include the library
#include "MQ-Sensor-SOLDERED.h"

// Predefined microcontroller pins for AO sensor pin (microcontroller dependent)
// You can change the pin to suit your setup.
#if defined(__AVR__) || defined(STM32)
#define SENSOR_ANALOG_PIN A1
#elif defined(ESP32)
#define SENSOR_ANALOG_PIN 34
#else
#define SENSOR_ANALOG_PIN 5
#endif

#define RatioMQ8CleanAir 70 // RS / R0 = 70 ppm

// Create library object for this specific sensor.
MQ2 mq8(SENSOR_ANALOG_PIN);

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    // Set math model to calculate the PPM concentration and the value of constants
    mq8.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq8.setA(976.97);
    mq8.setB(-0.688); // Configurate the ecuation values to get H2 concentration

    /*
      Exponential regression:
    GAS     | a      | b
    H2      | 976.97  | -0.688
    LPG     | 10000000 | -3.123
    CH4     | 80000000000000 | -6.666
    CO      | 2000000000000000000 | -8.074
    Alcohol | 76101 | -1.86
    */

    /*****************************  MQ Init ********************************************/
    // Remarks: Configure the pin of arduino as input.
    /************************************************************************************/
    mq8.begin(); // If you have easyC version of this sensor
                 // you should add here I2C address of sensor
                 // which is 0x30 by default and can be changed
                 // by onboard switches labeled with ADDR
    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq8.setRL(10);
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
        mq8.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq8.calibrate(RatioMQ8CleanAir);
        Serial.print(".");
    }
    mq8.setR0(calcR0 / 10);
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
    mq8.serialDebug(true);
}

void loop()
{
    mq8.update();      // Update data, the arduino will be read the voltage on the analog pin
    mq8.readSensor();  // Sensor will read PPM concentration using the model and a and b values setted before or in the
                       // setup
    mq8.serialDebug(); // Will print the table on the serial port
    delay(500);        // Sampling frequency
}
