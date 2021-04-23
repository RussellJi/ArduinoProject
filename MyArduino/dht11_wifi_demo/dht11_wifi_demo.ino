#include <SimpleDHT.h>
#include<ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "FAST_4ACE"
#define STAPSK  "abc13854816407"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 0
int pin_DHT11 = 0;
SimpleDHT11 dht11(pin_DHT11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
   // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  
  // DHT11 sampling rate is 0.2HZ.
  delay(5000);
}
