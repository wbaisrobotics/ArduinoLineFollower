#include <QTRSensors.h>

// The program running on the Arduino Mega of the 2019 FRC Team 4338 FIRST Deep Space Robot
// Captures information from two color sensors (left & right) and sends the data through DIO to the roborio

// Sensor grey cutoff
#define greyCutoff 500

// // Left

// Number of sensors used in the left side
#define leftSensorCount 16     

// Maximum timeout for sensors to be considered low in the left side
#define leftSensorTimeout 2500

// The 0th sensor in the left array
#define left0Pin 50
// The 1st sensor in the left array
#define left1Pin 52
// The 2nd sensor in the left array
#define left2Pin 46
// The 3rd sensor in the left array
#define left3Pin 48
// The 4th sensor in the left array
#define left4Pin 42
// The 5th sensor in the left array
#define left5Pin 44
// The 6th sensor in the left array
#define left6Pin 38
// The 7th sensor in the left array
#define left7Pin 40
// The 8th sensor in the left array
#define left8Pin 34
// The 9th sensor in the left array
#define left9Pin 36
// The 10th sensor in the left array
#define left10Pin 30
// The 11th sensor in the left array
#define left11Pin 32
// The 12th sensor in the left array
#define left12Pin 26
// The 13th sensor in the left array
#define left13Pin 28
// The 14th sensor in the left array
#define left14Pin 22
// The 15th sensor in the left array
#define left15Pin 24

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
#define right0Pin 51
// The 1st sensor in the right array
#define right1Pin 53
// The 2nd sensor in the right array
#define right2Pin 47
// The 3rd sensor in the right array
#define right3Pin 49
// The 4th sensor in the right array
#define right4Pin 43
// The 5th sensor in the right array
#define right5Pin 45
// The 6th sensor in the right array
#define right6Pin 39
// The 7th sensor in the right array
#define right7Pin 41
// The 8th sensor in the right array
#define right8Pin 35
// The 9th sensor in the right array
#define right9Pin 37
// The 10th sensor in the right array
#define right10Pin 31
// The 11th sensor in the right array
#define right11Pin 33
// The 12th sensor in the right array
#define right12Pin 27
// The 13th sensor in the right array
#define right13Pin 29
// The 14th sensor in the right array
#define right14Pin 23
// The 15th sensor in the right array
#define right15Pin 25

// Define the right sensor (given the defined constants above)
QTRSensorsRC rightSensor((unsigned char[]) {right0Pin, right1Pin, right2Pin, right3Pin, right4Pin, right5Pin, right6Pin, right7Pin, right8Pin, right9Pin, right10Pin, right11Pin, right12Pin, right13Pin, right14Pin, right15Pin},
  rightSensorCount, rightSensorTimeout, QTR_NO_EMITTER_PIN);
unsigned int rightSensorValues[rightSensorCount];

// Begin communication with the roborio
void setup()
{
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  Serial.setTimeout(10);
  //pinMode (7, INPUT);
}

// Loop, reading sensor values and writing to the roborio
void loop()
{
  // Read from the left sensor to the left sensor array
  leftSensor.read(leftSensorValues);

//  Serial.print ("Left:");
//  Serial.print ('\t');

  //Iterate through each left sensor value
  for (unsigned char i = 0; i < leftSensorCount; i++)
  {
    Serial.print(leftSensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }

  Serial.println();

  double lineLocLeft = findLine (leftSensorValues, leftSensorCount);

//  Serial.print ('\t');
//  Serial.print ("Left Line Location: ");
//  Serial.print(lineLocLeft);
//
//  Serial.print ('\t');

  // Read from the right sensor to the right sensor array
  rightSensor.read(rightSensorValues);

//  Serial.print ("Right:");
//  Serial.print ('\t');

  //Iterate through each right sensor value
//  for (unsigned char i = 0; i < rightSensorCount; i++)
//  {
//    Serial.print(rightSensorValues[i]);
//    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
//  }

  double lineLocRight = findLine (rightSensorValues, rightSensorCount);
//  Serial.print ('\t');
//  Serial.print ("Right Line Location: ");
//  Serial.print(lineLocRight);
//  if (digitalRead(7) == HIGH){
//    n = 0;
//  }
//  else{
//    if (Serial.readString() == "C"){
//      sprintf(buff, "%03d", n);
//      Serial.print(buff);
//    }
//  }

//  n++;
//  if (n > 99){
//    n = 0;
//  }
  double lineLoc;
  if (isnan (lineLocLeft) && isnan (lineLocRight)){
    // Set it to NaN
    lineLoc = lineLocLeft;
  }
  else if (isnan (lineLocLeft)){
    lineLoc = lineLocRight;
  }
  else if (isnan (lineLocRight)){
    lineLoc = 0 - (leftSensorCount - lineLocLeft);
  }
  else{
    lineLoc = lineLocRight - (leftSensorCount - lineLocLeft);
  }
  lineLoc = int((lineLoc + leftSensorCount) * (99/(leftSensorCount + rightSensorCount)));
  sendResult (lineLoc);
  
}

// Finds the line in an array of values
double findLine (unsigned int values[], int n)
{

  // Define the average
  double average = 0;
  // Define the complete sum
  double sum = 0;
  
  // Define an array for the normalized data
  int normValues [n];

  // Normalize the values and calculate a sum
  for (int i = 0; i < n; i++){
    
    // Normalize by subtracting the greyCutoff
    normValues[i] = greyCutoff - values [i];
    
    // If negative, set to 0
    if (normValues[i] < 0){ normValues[i] = 0;}

    // Add to the total sum
    sum += normValues[i];
    
  }

  // Iterate through each sensor value to calculate average
  for (int i = 0; i < n; i++){

    // Calculate weighted average
    average += (i+1) * (normValues[i]/sum);

  }

  // Return the line location
  return average;

}

// Buffer for converting the result to string
char buff[4];
// Sends the result through serial (with leading 0s)
void sendResult (int lineLocation){
    // Wait for send signal
    if (Serial.readString() == "C"){
      sprintf(buff, "%03d", lineLocation);
      Serial.print(buff);
    }
}

