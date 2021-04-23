#include <SoftwareSerial.h>

SoftwareSerial sw(2, 3); // RX, TX
int ledPin = 8;
int value;
void setup() {
 Serial.begin(115200);
 Serial.println("Interfacfing arduino with esp32");
 sw.begin(115200);
 pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, HIGH);
}

void loop() {
  if(sw.available()){
    value = sw.read();
    Serial.println("value:");
    Serial.println(value);  
    if(value=='1'){
      digitalWrite(ledPin, LOW);
    }
    if(value=='0'){
      digitalWrite(ledPin, HIGH);
    }
  }
}
