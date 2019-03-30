/*
 * Code Written By: Aman Ulla
 */
#include<Wire.h>    //including the Wire Library 
const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int val;
int redLed = 12;
int greenLed = 11;
int smokeA0 = A1;
int alcoholA0 = A0;
int sensorThres = 260;
void setup() {
  Wire.begin();      //Start the Wire Communication
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);    //Begin  the Serial Communication at 9600 baud rate
  pinMode(redLed, OUTPUT);    //configure the redled as OUTPUT
  pinMode(greenLed, OUTPUT);   //configure the greenled as OUTPUT
  pinMode(smokeA0, INPUT);    //Set the smoke sensor as InPUT
  pinMode(alcoholA0, INPUT);   // set the alcohol sensor as Input
  pinMode(13,HIGH);   
  digitalWrite(13,HIGH);
  Serial.begin(9600);
}
void loop() {
  int analogSensor = analogRead(smokeA0);    // read the smoke sensor data
  int alcohol = analogRead(alcoholA0);       // read the alcohol sensor data
  Serial.print("Smoke: ");
  Serial.println(analogSensor);             // display the smoke sensor value
  Serial.print("Alcohol: ");
  Serial.println(alcohol);                  // display the alcohol sensor value
  if (analogSensor > sensorThres)           // if the value crosses the threshold value then yello led glows
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
  if (alcohol > 500)      // if the alcohol value crosses the threshold value then yellow led glows
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
  delay(100);
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);    // Reading the Data from 6 axis Gyro
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ); 
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  delay(1000);
}

