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

  Example is modified by Soldered.com

 This example code is in the public domain.

*/

// Include the library
#include "MQ-Sensor-SOLDERED.h"

#define RatioMQ9CleanAir (9.6) // RS / R0 = 60 ppm

MQ9 mq9; // If this sensor is easyC, you don't need to specify on which
         // pin is connected

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    // Set math model to calculate the PPM concentration and the value of constants
    mq9.setRegressionMethod(1); //_PPM =  a*ratio^b


    /*****************************  MQ Init ********************************************/
    // Remarks: Initializes MQ easyC library.
    /************************************************************************************/
    mq9.begin(0x30); // Here you need to specify I2C address of sensor.
                     // By default it is set to 0x30, but you can change
                     // Using onboard switches labeled with ADDR
    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq9.setRL(10);
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
        mq9.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq9.calibrate(RatioMQ9CleanAir);
        Serial.print(".");
    }
    mq9.setR0(calcR0 / 10);
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
    Serial.println("** Lectures from MQ-9 ****");
    Serial.println("|    LPG   |  CH4 |   CO  |");
}

void loop()
{
    mq9.update(); // Update data, the arduino will be read the voltage on the analog pin
    /*
    Exponential regression:
    GAS     | a      | b
    LPG     | 1000.5 | -2.186
    CH4     | 4269.6 | -2.648
    CO      | 599.65 | -2.244
    */

    mq9.setA(1000.5);
    mq9.setB(-2.186);             // Configurate the ecuation values to get LPG concentration
    float LPG = mq9.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before
                                  // or in the setup

    mq9.setA(4269.6);
    mq9.setB(-2.648);             // Configurate the ecuation values to get LPG concentration
    float CH4 = mq9.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before
                                  // or in the setup

    mq9.setA(599.65);
    mq9.setB(-2.244);            // Configurate the ecuation values to get LPG concentration
    float CO = mq9.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before
                                 // or in the setup

    Serial.print("|    ");
    Serial.print(LPG);
    Serial.print("    |    ");
    Serial.print(CH4);
    Serial.print("    |    ");
    Serial.print(CO);
    Serial.println("    |");

    delay(500); // Sampling frequency
}
