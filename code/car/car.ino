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
}
void loop() {
char ch;
if(mySerial.available())
{
  ch=mySerial.read();
  Serial.println(ch);
  switch(ch)
  {
    case 'F':
      digitalWrite(9,HIGH);  //move forward
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      digitalWrite(12,LOW);
      delay(100);
      break;
    case 'B':
      digitalWrite(9,LOW);  //move backward
      digitalWrite(10,HIGH);
      digitalWrite(11,LOW);
      digitalWrite(12,HIGH);
      delay(100);
      break;
     case 'S':
       digitalWrite(9,LOW);  // stop
       digitalWrite(10,LOW);
       digitalWrite(11,LOW);
       digitalWrite(12,LOW);
       delay(100);
      break;
     case 'L':
       digitalWrite(9,HIGH);  //left 
       digitalWrite(10,LOW);
       digitalWrite(11,LOW);
       digitalWrite(12,HIGH);
       delay(100);
      break;
      case 'R':
       digitalWrite(9,LOW);  //right
       digitalWrite(10,HIGH);
       digitalWrite(11,HIGH);
       digitalWrite(12,LOW);
       delay(100);
       break; 
  }
}
}
