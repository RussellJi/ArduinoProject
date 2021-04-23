#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3);  //R T

const int GSR=A2;

float sensorValue;

void setup(){
  
  Serial.begin(9600);
  BT.begin(9600);
  BT.write("你好");
}

void loop(){
  int temp;
  sensorValue=analogRead(GSR);
  Serial.print("sensorValue=");
  Serial.println(sensorValue);
  BT.println(sensorValue);
  
}
