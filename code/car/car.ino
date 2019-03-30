/*
 * Code Written By: Aman Ulla
 */
#include <SoftwareSerial.h>    //importing the Bluetooth library
SoftwareSerial mySerial(5,6);   //connect 5 to rx and 6 to tx
const int motor_1_A;
const int motor_1_B;
const int motor_2_A;
const int motor_2_B;
void setup() { 
mySerial.begin(9600);     // Starting the Bluetooth Communication at 9600 Baud Rate
Serial.begin(9600);    // Starting the Serial Communication at 9600 Baud Rate
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
}
void loop() {
char ch;   // declaring variable to get the input from the bluetooth
if(mySerial.available())    //If there is any input available then enter the If 
{ 
  ch=mySerial.read();     //read the data from the bluetooth 
  Serial.println(ch);     // print the data on the Serial Monitor
  digitalWrite(13,HIGH);
  switch(ch)      
  {
    case 'F':      // if the character read is 'F' then move forward
      digitalWrite(9,HIGH);  //move forward
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      digitalWrite(12,LOW);
      delay(100);
      break;
    case 'B':     // if the character read is 'B' then move Backward
      digitalWrite(9,LOW);  //move backward   //2
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);
      digitalWrite(12,HIGH);
      delay(100);
      break;
     case 'S':    //if the character read is 'S' then stop all the motion
       digitalWrite(9,LOW);  // stop
       digitalWrite(10,LOW);
       digitalWrite(11,LOW);
       digitalWrite(12,LOW);
       delay(100);
      break;
     case 'L':          //if the character read is 'L' then move left direction
       digitalWrite(9,HIGH);  //left 
       digitalWrite(10,LOW);
       digitalWrite(11,LOW);
       digitalWrite(12,HIGH);
       delay(100);
      break;
      case 'R':      //if the character read is 'R' then move right  direction
       digitalWrite(9,LOW);  //right
       digitalWrite(10,HIGH);
       digitalWrite(11,HIGH);
       digitalWrite(12,LOW);
       delay(100);
       break; 
  }
}
digitalWrite(13,LOW);
}
