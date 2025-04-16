/**
 **************************************************
 *
 * @file        MQ-138.ino
 * @brief       Example for reading gas measurements from MQ138 sensor (native)
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

// Create an instance of the object
MQ138 mq138(SENSOR_ANALOG_PIN);

#define numOfCalibrations 10 //How many readings of R0 we take to get average measurement

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    // Initialize the sensor
    mq138.begin();
    /*****************************  MQ Calibration ********************************************/
    // Explanation:
    // In this routine the sensor will measure the resistance of the sensor after it has been pre-heated for 48h
    // and now is in a clean air enviorment, and it will setup the R0 value.
    // This routine not need to execute on every restart, you can load your R0 into flash memory and read it on startup
    
    Serial.print("Calibrating please wait.");
    bool calibrationResult=mq138.calibrateSensor(numOfCalibrations);
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
  mq138.update();      // Update data, read voltage level from sensor
  Serial.println("Toluene: " + String(mq138.readSensor())+"ppm"); // Print the readings to the serial monitor
  delay(500);        // Sampling frequency
}