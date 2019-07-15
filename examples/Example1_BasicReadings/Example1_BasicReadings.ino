/******************************************************************************
  SparkFun_TMP117_Breakout_Example.ino
  Example for the TMP117 I2C Temperature Sensor
  Madison Chodikov @ SparkFun Electronics
  May 29 2019
  ~

  This sketch configures the TMP117 temperature sensor and prints the
  temperature in degrees celsius and fahrenheit.

  Resources:
  Wire.h (included with Arduino IDE)
  SparkFunTMP117.h (included in the src folder)

  Development environment specifics:
  Arduino 1.8.9+
  Hardware Version 1

  This code is beerware; if you see me (or any other SparkFun employee) at
  the local, and you've found our code helpful, please buy us a round!

  Distributed as-is; no warranty is given.
******************************************************************************/

/*
  NOTE: For the most accurate readings:
  - Avoid heavy bypass traffic on the I2C bus
  - Use the highest available communication speeds
  - Use the minimal supply voltage acceptable for the system
  - Place device horizontally and out of any airflow when storing
  For more information on reaching the most accurate readings from the sensor,
  reference the "Precise Temperature Measurements with TMP116" datasheet that is
  linked on Page 35 of the TMP117's datasheet
*/

#include <Wire.h> // Used to establish serial communication on the I2C bus
#include <SparkFun_TMP117.h> // Used to send and recieve specific information from our sensor

// The default address of the device is 0x48 = 72 (GND)
// Sensor address can be changed with an external jumper to:
// VCC = 0x49 = 73
// SDA = 0x4A = 74
// SCL = 0x4B = 75
TMP117 sensor; // Initalize sensor


void setup()
{
  Wire.begin();
  Serial.begin(115200); // Start serial communication at 115200 baud
  Wire.setClock(400000); // Set clock speed to be the fastest for better communication (fast mode)
  sensor.setAddress(0x48);

  Serial.println("TMP117 Example 1: Basic Readings");
  if (sensor.begin() == true)
  {
    Serial.println("Begin");
  }
  else
  {
    Serial.println("Device failed to setup.");
    while (1);
  }
// Code commented out below for debugging purposes, delete once this sketch is finalized
//  uint16_t deviceID = sensor.readRegister(TMP117_DEVICE_ID);
//
//  Serial.print("deviceID: 0x");
//  Serial.println(deviceID, HEX);
//
//  Serial.print("deviceID: 0b");
//  Serial.println(deviceID, BIN);
//
//    while(1);
  
  sensor.isConnected();
}


void loop()
{
  if (sensor.dataReady() == true) // Function to make sure that there is data ready to be printed, only prints temperature values when data is ready
  {
    float tempC = sensor.readTempC();
    float tempF = sensor.readTempF();
    // Print temperature in C and F
    Serial.println(); // Create a white space for easier viewing
    Serial.print("Temperature in Celsius: %d", sensor.readTempC());
    Serial.println(tempC);
    Serial.print("Temperature in Fahrenheit: %d", sensor.readTempF());
    Serial.println(tempF);
    delay(500); // Delay added for easier readings
  
    /* Code below only for testing purposes */
    sensor.setConversionMode(3);
    uint8_t mode = sensor.getConversionMode();
    Serial.println(mode);
    
  }
  else
  {
    delay(500);
  }
  
}