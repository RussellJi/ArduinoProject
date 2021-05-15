#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define RXD0 3
#define TXD0 1

// Set these to your desired credentials.
const char *ssid = "YHA";
const char *password = "168168168";
WiFiServer server(8888);

void setup() {

  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,RXD0,TXD0);
  
  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.print(c);                    // print it out the serial monitor
        Serial2.write(c);
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
