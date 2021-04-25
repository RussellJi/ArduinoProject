//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include <Robojax_L298N_DC_motor.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
// motor 1 settings
#define CHA 0
#define ENA 25 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 33
#define IN2 32

// motor 2 settings
#define IN3 22
#define IN4 23
#define ENB 26// this pin must be PWM enabled pin if Arduino board is used
#define CHB 1

const int CCW = 2; // do not change
const int CW  = 1; // do not change

#define motor1 1 // do not change
#define motor2 2 // do not change

// for single motor
//Robojax_L298N_DC_motor robot(IN1, IN2, ENA, CHA, true);  

// for two motors without debug information // Watch video instruciton for this line: https://youtu.be/2JTMqURJTwg
//Robojax_L298N_DC_motor robot(IN1, IN2, ENA, CHA,  IN3, IN4, ENB, CHB);

// fore two motors with debut information
Robojax_L298N_DC_motor robot(IN1, IN2, ENA, CHA, IN3, IN4, ENB, CHB, true);


//注：电机GND一定与单片机GND相连
BluetoothSerial SerialBT;



void setup() {
 
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  robot.begin();
}
void forward()
{
  Serial.println("前进");
  robot.rotate(motor1, 70, CW);
  robot.rotate(motor2, 70, CW);
}
void back()
{
  Serial.println("后退");
  robot.rotate(motor1, 70, CCW);
  robot.rotate(motor2, 70, CCW);
}
void left()
{
  Serial.println("左转");
  robot.brake(1);
  robot.rotate(motor2, 70, CW);
}
void right()
{
  Serial.println("右转");
  robot.brake(2);
  robot.rotate(motor1, 70, CW);
}
void high()
{
  Serial.println("加速");
  robot.rotate(motor1, 80, CW);
  robot.rotate(motor2, 80, CW);
}
void low()
{
  Serial.println("减速");
  robot.rotate(motor1, 60, CW);
  robot.rotate(motor2, 60, CW);
}
void stop1()
{
  Serial.println("停止");
  robot.brake(1);
  robot.brake(2);
}
void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());

  }
  if (SerialBT.available()) {
//    Serial.write(SerialBT.read());
    String val = SerialBT.readString();
    
    Serial.println(val);
    char v2  = char(val[0]);
    SerialBT.write(v2);
    
    switch(v2){
      case '0':  
      digitalWrite(LED_BUILTIN, LOW);
      stop1();
      break;
      
      case '1':
      digitalWrite(LED_BUILTIN, HIGH);
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
  delay(20);
}
