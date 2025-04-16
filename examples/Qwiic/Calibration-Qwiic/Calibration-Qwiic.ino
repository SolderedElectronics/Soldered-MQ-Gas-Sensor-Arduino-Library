/**
 **************************************************
 *
 * @file        Calibration-Qwiic.ino
 * @brief       Example for calibrating an MQ sensor indefinitely
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


unsigned long counter = 0;

//Create an instance of the sensor object
MQ2 mq2; 

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    // Initialize I2C communication with the sensor
    mq2.begin(0x30); 

    Serial.println("MQ2 - Calibration");
    Serial.println("Note - Make sure you are in a clean room and the sensor has been pre-heating for almost 4 hours");
    Serial.println("Current calibration | R0 value");
}

void loop()
{
    mq2.update();
    // Read the sensor and print to serial monitor
    float lecture = mq2.calibrate(MQ2_config.Rs_R0_ratio);
    // Print in serial monitor
    Serial.print(counter);
    Serial.print(" | ");
    Serial.println(lecture);
    // Increment counter
    counter++;
    // Wait to measure next sample
    delay(400);
}
