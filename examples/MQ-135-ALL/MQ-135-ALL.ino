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

#define RatioMQ135CleanAir 3.6 // RS / R0 = 3.6 ppm

MQ135 mq135(SENSOR_PIN);

void setup()
{
    // Init the serial port communication - to debug the library
    Serial.begin(115200); // Init serial port

    // Set math model to calculate the PPM concentration and the value of constants
    mq135.setRegressionMethod(1); //_PPM =  a*ratio^b

    /*****************************  MQ Init ********************************************/
    // Remarks: Configure the pin of arduino as input.
    /************************************************************************************/
    mq135.begin();
    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq135.setRL(10);
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
        mq135.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq135.calibrate(RatioMQ135CleanAir);
        Serial.print(".");
    }
    mq135.setR0(calcR0 / 10);
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
    Serial.println("** Lectures from MQ-135 ****");
    Serial.println("|    CO   |  Alcohol |   CO2  |  Tolueno  |  NH4  |  Acteona  |");
}

void loop()
{
    mq135.update(); // Update data, the arduino will be read the voltage on the analog pin

    mq135.setA(605.18);
    mq135.setB(-3.937);            // Configurate the ecuation values to get CO concentration
    float CO = mq135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted
                                   // before or in the setup

    mq135.setA(77.255);
    mq135.setB(-3.18);                  // Configurate the ecuation values to get Alcohol concentration
    float Alcohol = mq135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted
                                        // before or in the setup

    mq135.setA(110.47);
    mq135.setB(-2.862);             // Configurate the ecuation values to get CO2 concentration
    float CO2 = mq135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted
                                    // before or in the setup

    mq135.setA(44.947);
    mq135.setB(-3.445);                 // Configurate the ecuation values to get Tolueno concentration
    float Tolueno = mq135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted
                                        // before or in the setup

    mq135.setA(102.2);
    mq135.setB(-2.473);             // Configurate the ecuation values to get NH4 concentration
    float NH4 = mq135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted
                                    // before or in the setup

    mq135.setA(34.668);
    mq135.setB(-3.369);                 // Configurate the ecuation values to get Acetona concentration
    float Acetona = mq135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted
                                        // before or in the setup

    Serial.print("|   ");
    Serial.print(CO);
    Serial.print("   |   ");
    Serial.print(Alcohol);
    Serial.print("   |   ");
    Serial.print(CO2);
    Serial.print("   |   ");
    Serial.print(Tolueno);
    Serial.print("   |   ");
    Serial.print(NH4);
    Serial.print("   |   ");
    Serial.print(Acetona);
    Serial.println("   |");
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

    delay(500); // Sampling frequency
}