//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#define IN4 26  //pwm2
#define IN3 34
#define IN2 25 //pwm1
#define IN1 32
//#define ENA 25
//#define ENB 26


//注：电机GND一定与单片机GND相连
BluetoothSerial SerialBT;

void car_init()
{
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN1, OUTPUT);
//  pinMode(ENA, OUTPUT);
//  pinMode(ENB, OUTPUT);
  dacWrite(IN2, 127);
  dacWrite(IN4, 127);
}

void setup() {
  car_init();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}
void car_control(int IN_1, int IN_2, int IN_3, int IN_4 )
{
  dacWrite(IN2, IN_2);
  dacWrite(IN4, IN_4);
  digitalWrite(IN1, IN_1);
//  digitalWrite(IN2, IN_2);
  digitalWrite(IN3, IN_3);
//  digitalWrite(IN4, IN_4);


}
void forward()
{
  car_control(1,255,1,255);
}
void back()
{
  car_control(0,255,0,255);
}
void left()
{
  car_control(0,0,1,255);
}
void right()
{
  car_control(1,255,0,0);
}
void high()
{
  car_control(1,255,1,255);
}
void low()
{
  car_control(1,80,1,80);
}
void stop1()
{
  car_control(0,0,0,0);
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
    
//    Serial.println(val);
    switch(v2){
      case '0':  
      digitalWrite(LED_BUILTIN, LOW);
      stop1();
      break;
      
      case '1':
      digitalWrite(LED_BUILTIN, HIGH);
//      digitalWrite(IN1, HIGH);
//      digitalWrite(IN2, LOW);
      forward();
      break;
      
      case '2':
      back();
//      digitalWrite(IN1, LOW);
//      digitalWrite(IN2, HIGH);
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
