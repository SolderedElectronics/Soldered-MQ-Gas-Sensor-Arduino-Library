/*
  MQUnifiedsensor Library - calibrating an MQ2

  Demonstrates the use a MQ2 sensor with easyC.
  Library originally added 01 may 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez

  Added example
  modified 27 May 2019
  by Miguel Califa

  Example is modified by Soldered.com

 This example code is in the public domain.

*/

// Include the library
#include "MQ-Sensor-SOLDERED.h"

double alcoholPPM = (0);
// Defaults, uncomment if you need
#define RatioMQ2CleanAir 9.83 // RS / R0 = 9.83 ppm
//#define RatioMQ3CleanAir 60   //RS / R0 = 60 ppm
//#define RatioMQ4CleanAir 4.4  //RS / R0 = 4.4 ppm
//#define RatioMQ5CleanAir 6.5  //RS / R0 = 6.5 ppm
//#define RatioMQ6CleanAir 10   //RS / R0 = 10 ppm
//#define RatioMQ7CleanAir 27.5 //RS / R0 = 27.5 ppm
//#define RatioMQ8CleanAir 70   //RS / R0 = 70 ppm
//#define RatioMQ9CleanAir 9.6  //RS / R0 = 9.6 ppm
//#define RatioMQ131CleanAir 15 //RS / R0 = 15 ppm
//#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm
//#define RatioMQ303CleanAir 1  //RS / R0 = 1 ppm
//#define RatioMQ309CleanAir 11 //RS / R0 = 11 ppm

unsigned long counter = 0;


MQ2 mq2; // If this sensor is easyC, you don't need to specify on which
         // pin is connected

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    mq2.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq2.setA(574.25);
    mq2.setB(-2.222); // Configurate the ecuation values to get LPG concentration
    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      MQ3.setRL(10);
    */
    // Initialize MQ easyC library.
    mq2.begin(0x30); // Here you need to specify I2C address of sensor.
                     // By default it is set to 0x30, but you can change
                     // Using onboard switches labeled with ADDR


    Serial.println("mq2 - Calibracion"); // Print in serial monitor
    Serial.println("Note - Make sure you are in a clean room and the sensor has pre-heated almost 4 hours");
    Serial.println("Autonumeric | lecture (R0)");
}

void loop()
{
    mq2.update();
    // Read the sensor and print in serial port
    float lecture = mq2.calibrate(RatioMQ2CleanAir);
    // Print in serial monitor
    Serial.print(counter);
    Serial.print(" | ");
    Serial.println(lecture);
    // Increment counter
    counter++;
    // Wait to measure next sample
    delay(400);
}
