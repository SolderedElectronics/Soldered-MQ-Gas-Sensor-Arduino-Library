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
  * @brief                   Initializes the sensor with a specific I2C address.
  *                          Overloaded function for virtual in base class to initialize sensor specific.
  * 
  * @param _addr             I2C address of the sensor
  * @return bool             True if initialization successful, false if I2C communication fails
  */
 bool MQ_Sensor::begin(int _addr)
 {
     if (_addr)
     {
         init(_addr);
         Wire.beginTransmission(_addr);
         if(Wire.endTransmission()!=0)
         {
             return false;
         }
     }
     setConfiguration(this->sensor_type);
     return true;
 }
 
 /**
  * @brief                   Initializes the sensor with a specific I2C address and custom configuration.
  *                          Overloaded function for virtual in base class to initialize sensor specific.
  * 
  * @param _addr             I2C address of the sensor
  * @param configcustom      Custom sensor configuration of type sensorType
  * @return bool             True if initialization successful, false if I2C communication fails
  */
 bool MQ_Sensor::begin(int _addr, sensorType configcustom)
 {
     if (_addr)
     {
         init(_addr);
         Wire.beginTransmission(_addr);
         if(Wire.endTransmission()!=0)
         {
             return false;
         }
     }
     else
     {
         if (aPin != -1)
             pinMode(aPin, INPUT);
         if (dPin != -1)
             pinMode(dPin, INPUT);
     }
     this->sensor_type=configcustom;
     setConfiguration(this->sensor_type);
     return true;
 }
 
 /**
  * @brief                   Initializes the sensor with default configuration.
  *                          Sets pin modes for analog and digital pins if they are defined.
  */
 void MQ_Sensor::begin()
 {
     if (aPin != -1)
         pinMode(aPin, INPUT);
     if (dPin != -1)
         pinMode(dPin, INPUT);
     setConfiguration(this->sensor_type);
 }
 
 /**
  * @brief                   Initializes the sensor with custom configuration.
  *                          Sets pin modes for analog and digital pins if they are defined.
  * 
  * @param configcustom      Custom sensor configuration of type sensorType
  */
 void MQ_Sensor::begin(sensorType configcustom)
 {
     if (aPin != -1)
         pinMode(aPin, INPUT);
     if (dPin != -1)
         pinMode(dPin, INPUT);
     this->sensor_type=configcustom;
     setConfiguration(this->sensor_type);
 }
 
 /**
  * @brief                   Reads the digital pin state of the sensor.
  *                          Overloaded function for virtual in base class to initialize sensor specific.
  *
  * @return bool             True if sensor is triggered, false otherwise
  */
 bool MQ_Sensor::digitalRead()
 {
     return ::digitalRead(dPin);
 }
 
 /**
  * @brief                   Sets the regression model parameters for the sensor based on given type.
  * 
  * @param type              Sensor type configuration containing regression method and coefficients
  */
 void MQ_Sensor::setRegressionModel(const sensorType& type)
 {
     this->setRegressionMethod(type.regression_method); //_PPM =  a*ratio^b
     this->setA(type.coefficient_a);
     this->setB(type.coefficient_b);
 }
 
 /**
  * @brief                   Checks if calibration value is valid (not infinite and not zero).
  * 
  * @param calcR0            Calculated R0 value to validate
  * @return bool             True if calibration value is valid, false otherwise
  */
 bool checkCalibration(float calcR0)
 {
     return !(isinf(calcR0) || calcR0 == 0);
 }
 
 /**
  * @brief                   Calibrates the sensor by taking multiple readings and averaging them.
  * 
  * @param numOfCalibrations Number of calibration readings to take
  * @return bool             True if calibration successful, false if calculated R0 is invalid
  */
 bool MQ_Sensor::calibrateSensor(int numOfCalibrations)
 {
     float calcR0 = 0;
     for (int i = 1; i <= numOfCalibrations; i++)
     {
         this->update(); // Update data, the arduino will be read the voltage on the analog pin
         calcR0 += this->calibrate(this->sensor_type.Rs_R0_ratio);
         Serial.print(".");
     }
     if(!checkCalibration(calcR0))
     {
         return false;
     }
     this->setR0(calcR0 / numOfCalibrations);
     return true;
 }
 
 /**
  * @brief                   Configures the sensor with the given sensor type parameters.
  * 
  * @param type              Sensor type configuration containing all necessary parameters
  */
 void MQ_Sensor::setConfiguration(sensorType& type)
 {
     this->setRegressionModel(type);
 }