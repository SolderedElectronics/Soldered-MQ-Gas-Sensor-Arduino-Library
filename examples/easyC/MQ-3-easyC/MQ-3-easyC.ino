/*
 MQUnifiedsensor Library - reading an MQ3

 Demonstrates the use a MQ3 sensor with easyC.
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

#define RatioMQ3CleanAir (60) // RS / R0 = 60 ppm

// Declare Sensor
MQ3 mq3; // If this sensor is easyC, you don't need to specify on which
         // pin is connected

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    // Set math model to calculate the PPM concentration and the value of constants
    mq3.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq3.setA(4.8387);
    mq3.setB(-2.68); // Configurate the ecuation values to get Benzene concentration
    /*
      Exponential regression:
    Gas    | a      | b
    LPG    | 44771  | -3.245
    CH4    | 2*10^31| 19.01
    CO     | 521853 | -3.821
    Alcohol| 0.3934 | -1.504
    Benzene| 4.8387 | -2.68
    Hexane | 7585.3 | -2.849
    */

    /*****************************  MQ Init ********************************************/
    // Remarks: Initializes MQ easyC library.
    /************************************************************************************/
    mq3.begin(0x30); // Here you need to specify I2C address of sensor.
                     // By default it is set to 0x30, but you can change
                     // Using onboard switches labeled with ADDR

    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq3.setRL(10);
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
        mq3.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq3.calibrate(RatioMQ3CleanAir);
        Serial.print(".");
    }
    mq3.setR0(calcR0 / 10);
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
    mq3.serialDebug(true);
}

void loop()
{
    mq3.update();      // Update data, the arduino will be read the voltage on the analog pin
    mq3.readSensor();  // Sensor will read PPM concentration using the model and a and b values setted before or in the
                       // setup
    mq3.serialDebug(); // Will print the table on the serial port
    delay(500);        // Sampling frequency
}
