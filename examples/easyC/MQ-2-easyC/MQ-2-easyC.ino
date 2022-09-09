/*
  MQUnifiedsensor Library - reading an MQ2

  Demonstrates the use a MQ2 sensor with easyC.
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

#define RatioMQ2CleanAir (9.83) // RS / R0 = 9.83 ppm

MQ2 mq2; // If this sensor is easyC, you don't need to specify on which
         // pin is connected


void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    // Set math model to calculate the PPM concentration and the value of constants
    mq2.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq2.setA(574.25);
    mq2.setB(-2.222); // Configurate the ecuation values to get LPG concentration
    /*
      Exponential regression:
      Gas    | a      | b
      H2     | 987.99 | -2.162
      LPG    | 574.25 | -2.222
      CO     | 36974  | -3.109
      Alcohol| 3616.1 | -2.675
      Propane| 658.71 | -2.168
    */

    /*****************************  MQ Init ********************************************/
    // Remarks: Initializes MQ easyC library.
    /************************************************************************************/

    mq2.begin(0x30); // Here you need to specify I2C address of sensor.
                     // By default it is set to 0x30, but you can change
                     // Using onboard switches labeled with ADDR

    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq2.setRL(10);
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
        mq2.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq2.calibrate(RatioMQ2CleanAir);
        Serial.print(".");
    }
    mq2.setR0(calcR0 / 10);
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

    mq2.serialDebug(true);
}

void loop()
{
    mq2.update();      // Update data, the arduino will be read the voltage on the analog pin
    mq2.readSensor();  // Sensor will read PPM concentration using the model and a and b values setted before or in the
                       // setup
    mq2.serialDebug(); // Will print the table on the serial port
    delay(500);        // Sampling frequency
}
