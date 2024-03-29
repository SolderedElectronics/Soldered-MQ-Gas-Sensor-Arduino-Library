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

 This example code is in the public domain.

*/

// Include the library
#include "MQ-Sensor-SOLDERED.h"

#define RatioMQ8CleanAir 70 // RS / R0 = 70 ppm

MQ8 mq8; // If this sensor is easyC, you don't need to specify on which
         // pin is connected

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
    // Remarks: Initializes MQ easyC library.
    /************************************************************************************/
    mq8.begin(0x30); // Here you need to specify I2C address of sensor.
                     // By default it is set to 0x30, but you can change
                     // Using onboard switches labeled with ADDR
    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq8.setRL(10);
    */
    /*****************************  MQ Calibration ********************************************/
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
        Serial.println("Warning: Conection issue founded! Check easyC cable, connector and I2C address!");
        while (1)
            ;
    }
    if (calcR0 == 0)
    {
        Serial.println("Warning: Conection issue founded! Check easyC cable, connector and I2C address!");
        while (1)
            ;
    }
    /*****************************  MQ Calibration ********************************************/
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
