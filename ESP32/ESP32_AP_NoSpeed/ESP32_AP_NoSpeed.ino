#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#include <ESP32Servo.h> 

Servo myservo;  // create servo object to control a servo
int servoPin = 25; 

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#define BUZZER 21
// motor 1 settings

#define IN1 33
#define IN2 32

// motor 2 settings
#define IN3 22
#define IN4 23

// Set these to your desired credentials.
const char *ssid = "YHA";
const char *password = "168168168";

WiFiServer server(8888);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
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
//  ESP32PWM::allocateTimer(0);
//  ESP32PWM::allocateTimer(1);
//  ESP32PWM::allocateTimer(2);
//  ESP32PWM::allocateTimer(3);
//  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(servoPin, 500, 2400);
  myservo.write(75);
}


void forward()
{
  myservo.write(75);
  Serial.println("前进");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(500);
  stop1();
}
void back()
{
  myservo.write(75);
  Serial.println("后退");
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
  delay(500);
  stop1();
}
void left_forward()
{
  myservo.write(110);
  Serial.println("左前");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
  stop1();
}
void left_back()
{
  myservo.write(110);
  Serial.println("左后");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
  delay(300);
  stop1();
}
void right_forward()
{
  myservo.write(40);
  Serial.println("右前");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(300);
  stop1();
}
void right_back()
{
  myservo.write(40);
  Serial.println("右后");
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(300);
  stop1();
}
//void high()
//{
//  Serial.println("加速");
//  robot.rotate(motor1, 80, CW);
//  robot.rotate(motor2, 80, CW);
//  delay(1000);
//  stop1();
//}
//void low()
//{
//  Serial.println("减速");
//  robot.rotate(motor1, 60, CW);
//  robot.rotate(motor2, 60, CW);
//  delay(1000);
//  stop1();
//}

void stop1()
{
  Serial.println("停止");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  myservo.write(75);

//  robot.brake(1);
//  robot.brake(2);
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
