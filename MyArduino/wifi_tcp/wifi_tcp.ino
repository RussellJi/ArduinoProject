#include <ESP8266WiFi.h>


#ifndef STASSID
#define STASSID "YHA"
#define STAPSK  "168168168"
#endif


int port = 8888;  //Port number
WiFiServer server(port);

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(STASSID, STAPSK);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
}
void loop() {
  // put your main code here, to run repeatedly:
    WiFiClient client = server.available();
     
    if (client) {
        if(client.connected())
        {
            Serial.println("Client Connected");
        }
         
        while(client.connected()){
            while(client.available()>0){
                // read data from the connected client
                Serial.write(client.read());
            }
            //Send Data to connected client
            while(Serial.available()>0)
            {
                client.write(Serial.read());
            }
        }
        client.stop();
        Serial.println("Client disconnected");
    }
}
