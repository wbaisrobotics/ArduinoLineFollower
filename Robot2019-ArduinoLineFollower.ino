#include <QTRSensors.h>

// The program running on the Arduino Mega of the 2019 FRC Team 4338 FIRST Deep Space Robot
// Captures information from two color sensors (left & right) and sends the data through DIO to the roborio

// // Left

// Number of sensors used in the left side
#define leftSensorCount 16     

// Maximum timeout for sensors to be considered low in the left side
#define leftSensorTimeout 2500

// The 0th sensor in the left array
#define left0Pin 53
// The 1st sensor in the left array
#define left1Pin 52
// The 2nd sensor in the left array
#define left2Pin 51
// The 3rd sensor in the left array
#define left3Pin 50
// The 4th sensor in the left array
#define left4Pin 49
// The 5th sensor in the left array
#define left5Pin 48
// The 6th sensor in the left array
#define left6Pin 47
// The 7th sensor in the left array
#define left7Pin 46
// The 8th sensor in the left array
#define left8Pin 45
// The 9th sensor in the left array
#define left9Pin 44
// The 10th sensor in the left array
#define left10Pin 43
// The 11th sensor in the left array
#define left11Pin 42
// The 12th sensor in the left array
#define left12Pin 41
// The 13th sensor in the left array
#define left13Pin 40
// The 14th sensor in the left array
#define left14Pin 39
// The 15th sensor in the left array
#define left15Pin 38

// Define the left sensor (given the defined constants above)
QTRSensorsRC leftSensor((unsigned char[]) {left0Pin, left1Pin, left2Pin, left3Pin, left4Pin, left5Pin, left6Pin, left7Pin, left8Pin, left9Pin, left10Pin, left11Pin, left12Pin, left13Pin, left14Pin, left15Pin},
  leftSensorCount, leftSensorTimeout, QTR_NO_EMITTER_PIN);
unsigned int leftSensorValues[leftSensorCount];


// // Right

// Number of sensors used in the right side
#define rightSensorCount 16     

// Maximum timeout for sensors to be considered low in the right side
#define rightSensorTimeout 2500

// The 0th sensor in the right array
#define right0Pin 3
// The 1st sensor in the right array
#define right1Pin 4
// The 2nd sensor in the right array
#define right2Pin 5
// The 3rd sensor in the right array
#define right3Pin 6
// The 4th sensor in the right array
#define right4Pin 7
// The 5th sensor in the right array
#define right5Pin 8
// The 6th sensor in the right array
#define right6Pin 9
// The 7th sensor in the right array
#define right7Pin 10
// The 8th sensor in the right array
#define right8Pin 11
// The 9th sensor in the right array
#define right9Pin 12
// The 10th sensor in the right array
#define right10Pin 13
// The 11th sensor in the right array
#define right11Pin 14
// The 12th sensor in the right array
#define right12Pin 15
// The 13th sensor in the right array
#define right13Pin 16
// The 14th sensor in the right array
#define right14Pin 17
// The 15th sensor in the right array
#define right15Pin 18

// Define the right sensor (given the defined constants above)
//QTRSensorsRC rightSensor((unsigned char[]) {right0Pin, right1Pin, right2Pin, right3Pin, right4Pin, right5Pin, right6Pin, right7Pin, right8Pin, right9Pin, right10Pin, right11Pin, right12Pin, right13Pin, right14Pin, right15Pin},
//  rightSensorCount, rightSensorTimeout, QTR_NO_EMITTER_PIN);
unsigned int rightSensorValues[rightSensorCount];

// Begin communication with the roborio
void setup()
{
  delay(500);
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(1000);
}


// Loop, reading sensor values and writing to the roborio
void loop()
{
  // Read from the left sensor to the left sensor array
  leftSensor.read(leftSensorValues);

  // Iterate through each left sensor value
  for (unsigned char i = 0; i < leftSensorCount; i++)
  {
    Serial.print(leftSensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();

  delay(250);
  
}
