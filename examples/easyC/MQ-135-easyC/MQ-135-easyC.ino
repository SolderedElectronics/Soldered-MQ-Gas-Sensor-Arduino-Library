/*
  MQUnifiedsensor Library - reading an mq135

  Demonstrates the use a mq135 sensor.
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

#define RatioMQ135CleanAir 3.6 // RS / R0 = 3.6 ppm

MQ135 mq135; // If this sensor is easyC, you don't need to specify on which
             // pin is connected

void setup()
{
    // Init the serial port communication - to debug the library
    Serial.begin(115200); // Init serial port

    // Set math model to calculate the PPM concentration and the value of constants
    mq135.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq135.setA(102.2);
    mq135.setB(-2.473); // Configurate the ecuation values to get NH4 concentration

    /*
      Exponential regression:
    GAS      | a      | b
    CO       | 605.18 | -3.937
    Alcohol  | 77.255 | -3.18
    CO2      | 110.47 | -2.862
    Tolueno  | 44.947 | -3.445
    NH4      | 102.2  | -2.473
    Acetona  | 34.668 | -3.369
    */

    /*****************************  MQ Init ********************************************/
    // Remarks: Initializes MQ easyC library.
    /************************************************************************************/
    mq135.begin(0x30); // Here you need to specify I2C address of sensor.
                       // By default it is set to 0x30, but you can change
                       // Using onboard switches labeled with ADDR

    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq135.setRL(10);
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
        mq135.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq135.calibrate(RatioMQ135CleanAir);
        Serial.print(".");
    }
    mq135.setR0(calcR0 / 10);
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
    mq135.serialDebug(true);
}

void loop()
{
    mq135.update();     // Update data, the arduino will be read the voltage on the analog pin
    mq135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the
                        // setup
    mq135.serialDebug(); // Will print the table on the serial port
    delay(500);          // Sampling frequency
}
