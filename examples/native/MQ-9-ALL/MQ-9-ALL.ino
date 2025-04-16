/**
 **************************************************
 *
 * @file        MQ-9.ino
 * @brief       Example for reading all supported gas measurements from MQ9 sensor (native)
 *
 *              To successfully run the sketch:
 *              - Connect the breakout to your Dasduino board via the I2C pins
 *              - Run the sketch and open serial monitor at 115200 baud!
 *
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 * @authors     Josip Šimun @ soldered.com
 * Special thanks to Miguel Califa for example template
 ***************************************************/

// Include the library
#include "MQ-Sensor-SOLDERED.h"

// Predefined microcontroller pins for AO sensor pin (microcontroller dependent)
// You can change the pin to suit your setup.
#if defined(__AVR__) || defined(STM32)
#define SENSOR_ANALOG_PIN A1
#elif defined(ESP32)
#define SENSOR_ANALOG_PIN 34
#else
#define SENSOR_ANALOG_PIN 5
#endif

#define numOfCalibrations 10 //How many readings of R0 we take to get average measurement

// Create an instance of the object
MQ9 mq9(SENSOR_ANALOG_PIN);


float LPG,CO,CH4; //Values we will read

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    mq9.begin(); 

    /*****************************  MQ Calibration ********************************************/
    // Explanation:
    // In this routine the sensor will measure the resistance of the sensor after it has been pre-heated for 48h
    // and now is in a clean air enviorment, and it will setup the R0 value.
    // This routine not need to execute on every restart, you can load your R0 into flash memory and read it on startup
    
    Serial.print("Calibrating please wait.");
    bool calibrationResult=mq9.calibrateSensor(numOfCalibrations);
    if(!calibrationResult) //Check if the sensor was properly calibrated
    {
      Serial.println("There was an error reading the sensor, check connection and try again");
      while(1)
      {}
    }
    Serial.print("Calibration done!");

    /*****************************  MQ Calibration ********************************************/
}

void loop()
{
  mq9.update();      // Update data, read voltage level from sensor
  
  // Since the MQ9 sensors gives accurate readings for the gasses it can detect, we will read all
  // of their values

  // We have to define the a and b constants for eachg curve of each gas

  /*
    Exponential regression:
    GAS     | a      | b
    LPG     | 1000.5 | -2.186
    CH4     | 4269.6 | -2.648
    CO      | 599.65 | -2.244
  */
    
  //LPG
  mq9.setA(1000.5);
  mq9.setB(-2.186);
  LPG=mq9.readSensor();

  //CH4
  mq9.setA(4269.6);
  mq9.setB(-2.648);
  CH4=mq9.readSensor();

  //CO
  mq9.setA(599.65);
  mq9.setB(-2.244);
  CO=mq9.readSensor();

  //Printing all values in form | LPG | CH4 | CO | in ppm
  Serial.println("| "+String(LPG)+" | "+String(CH4)+" | "+String(CO)+" |");
  
  delay(1000);        // Sampling frequency
}