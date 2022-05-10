/*
  MQUnifiedsensor Library - smokeDetector

  Demonstrates the use a MQ2 sensor.
  Library originally added 01 may 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez

  Added example
  modified 23 May 2019
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

#define RatioMQ4CleanAir 4.4 // RS / R0 = 4.4 ppm

// Declare Sensor
MQ4 mq4(SENSOR_PIN); // If you have easyC version of this sensor
                     // just plug it in microcontroller and
                     // remove this "(SENSOR_PIN)" because sensor
                     // is not connected to pin but on I2C bus

void setup()
{
    // Init serial port
    Serial.begin(115200);
    // Set math model to calculate the PPM concentration and the value of constants
    mq4.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq4.setA(30000000);
    mq4.setB(-8.308); // Configurate the ecuation values to get CH4 concentration
    /*
      Exponential regression:
    Gas    | a      | b
    LPG    | 3811.9 | -3.113
    CH4    | 1012.7 | -2.786
    CO     | 200000000000000 | -19.05
    Alcohol| 60000000000 | -14.01
    smoke  | 30000000 | -8.308
    */
    /*****************************  MQ Init ********************************************/
    // Remarks: Configure the pin of arduino as input.
    /************************************************************************************/
    mq4.begin(); // If you have easyC version of this sensor
                 // you should add here I2C address of sensor
                 // which is 0x30 by default and can be changed
                 // by onboard switches labeled with ADDR
    /*
     //If the RL value is different from 10K please assign your RL value with the following method:
     mq4.setRL(10);
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
        mq4.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq4.calibrate(RatioMQ4CleanAir);
        Serial.print(".");
    }
    mq4.setR0(calcR0 / 10);
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
    mq4.serialDebug(true);
}

void loop()
{
    /*****************************  MQReadSensor  ****************************************
    Input:   Gas - Serial print flag
    Output:  Value in PPM
    Remarks: This function use readPPM to read the value in PPM the gas in the air.
    ************************************************************************************/
    // Read the sensor and print in serial port
    // Lecture will be saved in lecture variable
    mq4.update();
    float smokePPM = mq4.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted
                                       // before or in the setup
    if (smokePPM > 1000)
        Serial.println("Warning: High concentrations of smoke detected");

    mq4.serialDebug(); // Will print the table on the serial port
    delay(400);
}
