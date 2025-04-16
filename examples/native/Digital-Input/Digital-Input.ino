/**
 **************************************************
 *
 * @file        Digital-Input.ino
 * @brief       Example of using the digital pin to detect a high gas concentration
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

// DO of the sensor is connected to pin 2 of the microcontroller.
#define SENSOR_DIGITAL_PIN 2

// Create library object for this specific sensor.
MQ135 mq135(SENSOR_ANALOG_PIN,SENSOR_DIGITAL_PIN); // Connect sensor to analog input A1, digital pin 2 for digitalRead

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);
}

void loop()
{
    //
    if (mq135.digitalRead())
    {
        Serial.println("Alarm high concentrations detected");
    }
    else
    {
        Serial.println("Status: Normal");
    }

    delay(1000);
}