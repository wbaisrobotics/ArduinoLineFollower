#include <QTRSensors.h>

// The program running on the Arduino Mega of the 2019 FRC Team 4338 FIRST Deep Space Robot
// Captures information from two color sensors (left & right) and sends the data through DIO to the roborio

// // Left

// number of sensors used in the left side
#define leftSensorCount   16     

// waits for 2500 microseconds for sensor outputs to go low in the left side
#define leftSensorTimeout       2500

// The 0th sensor in the left array
#define left0Pin 3
// The 1st sensor in the left array
#define left1Pin 4
// The 2nd sensor in the left array
#define left2Pin 5
// The 3rd sensor in the left array
#define left3Pin 6
// The 4th sensor in the left array
#define left4Pin 7
// The 5th sensor in the left array
#define left5Pin 8
// The 6th sensor in the left array
#define left6Pin 9
// The 7th sensor in the left array
#define left7Pin 10
// The 8th sensor in the left array
#define left8Pin 11
// The 9th sensor in the left array
#define left9Pin 12
// The 10th sensor in the left array
#define left10Pin 13
// The 11th sensor in the left array
#define left11Pin 14
// The 12th sensor in the left array
#define left12Pin 15
// The 13th sensor in the left array
#define left13Pin 16
// The 14th sensor in the left array
#define left14Pin 17
// The 15th sensor in the left array
#define left15Pin 18

// Define the left sensor
QTRSensorsRC qtrrc((unsigned char[]) {left0Pin, left1Pin, left2Pin, left3Pin, left4Pin, left5Pin, left6Pin, left7Pin, left8Pin, left9Pin, left10Pin, left11Pin, left12Pin, left13Pin, left14Pin, left15Pin},
  leftSensorCount, leftSensorTimeout, QTR_NO_EMITTER_PIN);
unsigned int sensorValues[leftSensorCount];


void setup()
{
  delay(500);
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(1000);
}


void loop()
{
  // read raw sensor values
  qtrrc.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum reflectance and
  // 2500 means minimum reflectance
  for (unsigned char i = 0; i < leftSensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();

  delay(250);
}
