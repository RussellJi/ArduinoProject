#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#include <Robojax_L298N_DC_motor.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#define BUZZER 21
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

// fore two motors with debut information
Robojax_L298N_DC_motor robot(IN1, IN2, ENA, CHA, IN3, IN4, ENB, CHB, true);

// Set these to your desired credentials.
const char *ssid = "YHA";
const char *password = "168168168";

WiFiServer server(8888);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
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
  Serial.println("前进");
  robot.rotate(motor1, 60, CW);
  robot.rotate(motor2, 60, CW);
  delay(1000);
  stop1();
}
void back()
{
  Serial.println("后退");
  robot.rotate(motor1, 60, CCW);
  robot.rotate(motor2, 60, CCW);
  delay(1000);
  stop1();
}
void left_forward()
{
  Serial.println("左前");
  robot.brake(1);
  robot.rotate(motor2, 57, CW);
  delay(1600);
  stop1();
}
void left_back()
{
  Serial.println("左后");
  robot.brake(1);
  robot.rotate(motor2, 57, CCW);
  delay(1600);
  stop1();
}
void right_forward()
{
  Serial.println("右前");
  robot.brake(2);
  robot.rotate(motor1, 57, CW);
  delay(1600);
  stop1();
}
void right_back()
{
  Serial.println("右后");
  robot.brake(2);
  robot.rotate(motor1, 57, CCW);
  delay(1600);
  stop1();
}
void high()
{
  Serial.println("加速");
  robot.rotate(motor1, 80, CW);
  robot.rotate(motor2, 80, CW);
  delay(1000);
  stop1();
}
void low()
{
  Serial.println("减速");
  robot.rotate(motor1, 60, CW);
  robot.rotate(motor2, 60, CW);
  delay(1000);
  stop1();
}

void stop1()
{
  Serial.println("停止");
  robot.brake(1);
  robot.brake(2);
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
//        client.write(str.c_str("ACK:"+c));
//        client.print("ACK"+c);
        client.write("ACK");
        client.write(c);

        Serial.write(c);                    // print it out the serial monitor

        switch(c){
        case '0':  
        stop1();
        break;
        
        case '2':
        forward();
        break;
        
        case '8':   
        back();
        break;
        
        case '1':
        left_forward();
        break;
        
        case '3':
        right_forward();
        break;
        
        case '7':
        left_back();
        break;
  
        case '9':
        right_back();
        break;

        case '4':
        digitalWrite(LED_BUILTIN, HIGH);
        break;

        case '6':
        digitalWrite(LED_BUILTIN, LOW);
        break;

        case '5':
        digitalWrite(BUZZER, LOW);
        delay(1000);
        digitalWrite(BUZZER, HIGH);
        break;
        
      }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
