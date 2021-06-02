#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <Robojax_L298N_DC_motor.h>


void TaskTcpConnect1( void *pvParameters );
void TaskTcpConnect2(void *pvParameters);

#define LED_BUILTIN 19   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#define BUZZER 21  //+~vcc  -~21
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

// fore two motors without debut information
Robojax_L298N_DC_motor robot(IN1, IN2, ENA, CHA, IN3, IN4, ENB, CHB, false);

// Set these to your desired credentials.
const char *ssid = "YHA";
const char *password = "168168168";

WiFiServer server(8888);

void forward()
{

  Serial.println("前进");
  robot.rotate(motor1, 60, CW);
  robot.rotate(motor2, 60, CW);

}
void back()
{
  Serial.println("后退");
  robot.rotate(motor1, 60, CCW);
  robot.rotate(motor2, 60, CCW);
}

void left_forward()
{
  Serial.println("左前");

  robot.brake(1);
  robot.rotate(motor2, 60, CW);
  
}
void left_back()
{
  Serial.println("左后");
  robot.brake(1);
  robot.rotate(motor2, 60, CCW);
      
}
void right_forward()
{

  Serial.println("右前");
  robot.brake(2);
  robot.rotate(motor1, 60, CW);

}
void right_back()
{

  Serial.println("右后");
  robot.brake(2);
  robot.rotate(motor1, 60, CCW);
  delay(300);
  stop1();
}

void stop1()
{
  Serial.println("停止");
  robot.brake(1);
  robot.brake(2);
  digitalWrite(LED_BUILTIN, LOW);
}

void light()
{
  digitalWrite(LED_BUILTIN, HIGH);
}

void Task1code( void * parameter) {
  while(1){
    Serial.print("Task1 running on core ");
    Serial.println(xPortGetCoreID());
  }
 
}
void Task2code( void * parameter) {
  while(1){
    Serial.print("Task1 running on core ");
    Serial.println(xPortGetCoreID());
  }
}

void setup() 
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
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
  xTaskCreatePinnedToCore(
    TaskTcpConnect1
//    Task1code
    ,  "TaskBlink"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
    TaskTcpConnect2
//    Task2code
    ,  "AnalogReadA3"
    ,  1024  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);
}


void loop() 
{   
  
}

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
    
  If you want to know what pin the on-board LED is connected to on your ESP32 model, check
  the Technical Specs of your board.
*/

  // initialize digital LED_BUILTIN on pin 13 as an output.
//  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    Serial.print("Task1 running on core ");
    Serial.println(xPortGetCoreID());
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay(100);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskTcpConnect1(void *pvParameters)
{
  (void) pvParameters;
  
  while(1){
    WiFiClient client = server.available();   // listen for incoming clients
//    Serial.print("Task1 running on core ");
//    Serial.println(xPortGetCoreID());
    if (client) {                             // if you get a client,
    Serial.println("New Client.");
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) { 
        char c = client.read();
        Serial.print(c);
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
  }
  
}
void TaskTcpConnect2(void *pvParameters)
{
  (void) pvParameters;
 
  while(1){
     WiFiClient client = server.available();   // listen for incoming clients
//    Serial.print("Task1 running on core ");
//    Serial.println(xPortGetCoreID());
    if (client) {                             // if you get a client,
    Serial.println("New Client.");
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) { 
        char c = client.read();
        Serial.print(c);
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
  }
  
}
