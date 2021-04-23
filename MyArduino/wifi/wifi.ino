#include<ESP8266WiFi.h>
#ifndef STASSID
#define STASSID "FAST_4ACE"
#define STAPSK  "abc13854816407"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
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

}
