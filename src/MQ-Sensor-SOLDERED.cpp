/**
 **************************************************
 *
 * @file        MQ-Sensor-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Zvonimir Haramustek for soldered.com
 ***************************************************/


#include "MQ-Sensor-SOLDERED.h"


/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void MQ_Sensor::begin()
{
    if (aPin != -1)
        pinMode(aPin, INPUT);
    if (dPin != -1)
        pinMode(dPin, INPUT);
}

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 *
 * @returns bool            Is sensor triggered
 */
bool MQ_Sensor::digitalRead()
{
    return ::digitalRead(dPin);
}