#include "BluetoothSerial.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <Robojax_L298N_DC_motor.h>   

#define CHA 0
#define ENA 25 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 33
#define IN2 32

#define IN3 22
#define IN4 23
#define ENB 26// this pin must be PWM enabled pin if Arduino board is used
#define CHB 1

const int CCW = 2; // do not change
const int CW  = 1; // do not change

#define motor1 1 // do not change
#define motor2 2 // do not change


Robojax_L298N_DC_motor robot(IN1, IN2, ENA, CHA, IN3, IN4, ENB, CHB, true);

const char *ssid = "YHA";
const char *password = "168168168";

BluetoothSerial SerialBT;
WiFiServer server(8888);

void setup() {
  Serial.begin(115200);
  SerialBT.begin("YHA"); //Bluetooth device name
  
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
  robot.begin();
}

void forward()
{
  robot.rotate(motor1, 70, CW);
  robot.rotate(motor2, 70, CW);
}
void back()
{
  robot.rotate(motor1, 70, CCW);
  robot.rotate(motor2, 70, CCW);
}
void left()
{
  robot.brake(1);
  robot.rotate(motor2, 70, CW);
}
void right()
{
  robot.brake(2);
  robot.rotate(motor1, 70, CW);
}
void high()
{
  robot.rotate(motor1, 80, CW);
  robot.rotate(motor2, 80, CW);
}
void low()
{
  robot.rotate(motor1, 60, CW);
  robot.rotate(motor2, 60, CW);
}
void stop1()
{
  robot.brake(1);
  robot.brake(2);

}

void loop() {
  if (SerialBT.available()) {
    String val = SerialBT.readString();
    Serial.println(val);
    char v2  = char(val[0]);
    switch(v2){
      case '0':  
      stop1();
      break;
      case '1':
      forward();
      break;
      case '2':
      back();
      break;
      case '3':
      left();
      break;
      case '4':
      right();
      break;
      case '5':
      high();
      break;
      case '6':
      low();
      break;
    }
    
  }
  
  WiFiClient client = server.available();   // listen for incoming clients
  
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        switch(c){
        case '0':  
        stop1();
        break;
        case '1':
        forward();
        break;
        case '2':
        back();
        break;
        case '3':
        left();
        break;
        case '4':
        right();
        break;
        case '5':
        high();
        break;
        case '6':
        low();
        break;
      }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
