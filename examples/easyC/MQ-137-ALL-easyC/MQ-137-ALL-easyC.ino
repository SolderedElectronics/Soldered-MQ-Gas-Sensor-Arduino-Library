/*
  MQUnifiedsensor Library - reading an MQ137

  Demonstrates the use of an MQ137 sensor.
  Library originally added 01 May 2019
  by Miguel A Califa, Yersson Carrillo, Ghiordy Contreras, Mario Rodriguez

  Modified to work with MQ137 Ammonia Gas Sensor
  by Robert@Soldered.com

  Wiring:
  Connect the sensor to your Dasduino board via an easyC cable or using the I2C pins

  This example code is in the public domain.
*/

// Include the library
#include "MQ-Sensor-SOLDERED.h"

#define Ratiomq137CleanAir 27

MQ137 mq137;

void setup()
{
    // Init the serial port communication - to debug the library
    Serial.begin(115200);

    // Set math model to calculate the PPM concentration and the value of constants
    mq137.setRegressionMethod(1); //_PPM =  a*ratio^b
    // Set the constants a and b for NH3 (Ammonia) from the datasheet
    mq137.setA(605.18);
    mq137.setB(-3.937);

    /*****************************  MQ Init ********************************************/
    // Remarks: Initializes MQ easyC library.
    /************************************************************************************/
    mq137.begin(0x30); // Here you need to specify I2C address of sensor.
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
        mq137.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq137.calibrate(Ratiomq137CleanAir);
        Serial.print(".");
    }
    mq137.setR0(calcR0 / 10);
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
    // Print header
    Serial.println();
    Serial.print("|     ");
    Serial.print("NH3");
    Serial.println("     |");
}

void loop()
{
    mq137.update();
    float NH3 = mq137.readSensor();
    Serial.print("|     ");
    Serial.print(NH3);
    Serial.println("     |");
    delay(500); // Sampling frequency
}