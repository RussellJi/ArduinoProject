/*
  UDPSendReceive.pde:
  This sketch receives UDP message strings, prints them to the serial port
  and sends an "acknowledge" string back to the sender

  A Processing sketch is included at the end of file that can be used to send
  and received messages for testing with a computer.

  created 21 Aug 2010
  by Michael Margolis

  This code is in the public domain.

  adapted from Ethernet library examples
*/


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "YHA"
#define STAPSK  "168168168"
#endif

unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged\r\n";       // a string to send back

WiFiUDP Udp;

void setup() {
//  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(STASSID, STAPSK);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
//    Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d, free heap = %d B)\n",
//                  packetSize,
//                  Udp.remoteIP().toString().c_str(), Udp.remotePort(),
//                  Udp.destinationIP().toString().c_str(), Udp.localPort(),
//                  ESP.getFreeHeap());

    // read the packet into packetBuffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
//    switch(packetBuffer[0]){
//      case '0':
//          digitalWrite(LED_BUILTIN,0);
//          break;
//      case '':
//          digitalWrite(LED_BUILTIN,1);
//          break;
//    }

    packetBuffer[n] = 0;
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    if(packetBuffer[4]=='0'){
      digitalWrite(LED_BUILTIN,0);
    }
    if(packetBuffer[4]=='1'){
      digitalWrite(LED_BUILTIN,1);
    }
    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }

}
