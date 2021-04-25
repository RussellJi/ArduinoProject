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

BluetoothSerial SerialBT;



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  
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
      break;
      case '1':
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    }
    
//    if (val == "1") {
//      digitalWrite(LED_BUILTIN, HIGH);
//    }
//    if (val == "0") {
//      digitalWrite(LED_BUILTIN, LOW);
//    }
  }
  delay(20);
}
