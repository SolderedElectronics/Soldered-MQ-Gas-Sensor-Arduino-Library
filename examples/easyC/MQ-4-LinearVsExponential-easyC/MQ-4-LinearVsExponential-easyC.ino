/*
  MQUnifiedsensor Library - reading an MQ4

  Demonstrates the use a MQ4 sensor with easyC.
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

#define RatioMQ4CleanAir 4.4 // RS / R0 = 4.4 ppm

MQ4 mq4; // If this sensor is easyC, you don't need to specify on which
         // pin is connected

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    /*****************************  MQ Init ********************************************/
    // Remarks: Initializes MQ easyC library.
    /************************************************************************************/
    mq4.begin(0x30); // Here you need to specify I2C address of sensor.
                     // By default it is set to 0x30, but you can change
                     // Using onboard switches labeled with ADDR

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
        mq4.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq4.calibrate(RatioMQ4CleanAir);
        Serial.print(".");
    }
    mq4.setR0(calcR0 / 10);
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

    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq4.setRL(10);
    */

    /*****************************  MQ Init ********************************************/
    // Input: setup flag, if this function are on setup will print the headers (Optional - Default value: False)
    // Output: print on serial port the information about sensor and sensor readings
    // Remarks: Configure the pin of arduino as input.
    /************************************************************************************/
    mq4.begin(); // If you have easyC version of this sensor
                 // you should add here I2C address of sensor
                 // which is 0x30 by default and can be changed
                 // by onboard switches labeled with ADDR

    Serial.println("** Lectures from MQ-4**********");
    Serial.println("|      LPG (Linear EQ)        |         LPG (Exponential EQ)      |");
}

void loop()
{
    mq4.update(); // Update data, the arduino will be read the voltage on the analog pin

    // https://jayconsystems.com/blog/understanding-a-gas-sensor
    // Set math model to calculate the PPM concentration and the value of constants
    mq4.setRegressionMethod(0); //_PPM =  pow(10, (log10(ratio)-b)/a)
    mq4.setA(-0.318);
    mq4.setB(1.133);               // A -> Slope, B -> Intersect with X - Axis
    float LPG1 = mq4.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted
                                   // before or in the setup

    // Set math model to calculate the PPM concentration and the value of constants
    mq4.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq4.setA(1012.7);
    mq4.setB(-2.786);              // Configurate the ecuation values to get CH4 concentration
    float LPG2 = mq4.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted
                                   // before or in the setup

    //  exposure to 2000 ppm of LPG gas is immediately dangerous to life and health. In this section
    if (LPG1 >= 2000 || LPG2 >= 2000)
        Serial.println("Warning - Very high concentrations detected!");

    Serial.print("|              ");
    Serial.print(LPG1);
    Serial.print("            |           ");
    Serial.print(LPG2);
    Serial.println("          |");

    delay(500); // Sampling frequency
}
