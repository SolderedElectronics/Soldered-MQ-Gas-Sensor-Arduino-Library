/*
  MQUnifiedsensor Library - reading an MQ131

  Demonstrates the use a MQ131 sensor with easyC.
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

#define Ratiomq131CleanAir 15 //RS / R0 = 15 ppm

MQ131 mq131; // If this sensor is easyC, you don't need to specify on which
             // pin is connected

void setup()
{
  // Init the serial port communication at 115200 bauds. It's used to print out measured data.
  Serial.begin(115200);

  // Set math model to calculate the PPM concentration and the value of constants
  mq131.setRegressionMethod(1); //_PPM =  a*ratio^b

  /*****************************  MQ Init ********************************************/
  // Remarks: Initializes MQ easyC library.
  /************************************************************************************/
  mq131.begin(0x30); // Here you need to specify I2C address of sensor.
                     // By default it is set to 0x30, but you can change
                     // Using onboard switches labeled with ADDR
  /*
    //If the RL value is different from 10K please assign your RL value with the following method:
    mq131.setRL(10);
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
    mq131.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += mq131.calibrate(Ratiomq131CleanAir);
    Serial.print(".");
  }
  mq131.setR0(calcR0 / 10);
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
    Exponential regression:
  GAS     | a      | b
  NOx     | -462.43 | -2.204
  CL2     | 47.209 | -1.186
  O3      | 23.943 | -1.11
  */

  mq131.setA(23.943);
  mq131.setB(-1.11);             // Configurate the ecuation values to get O3 concentration

  // Now let's read the values in the loop:
  Serial.println("** Readings from MQ-131 ****");
  Serial.println("O3 in PPM: ");
}

void loop()
{
  mq131.update(); // Update data, the arduino will be read the voltage on the analog pin

  float O3 = mq131.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted
                                  // before or in the setup

  //_PPM =  a*ratio^b

  Serial.println(O3);

  delay(500); // Sampling frequency
}
