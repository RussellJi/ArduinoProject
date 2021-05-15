#include <SoftwareSerial.h>
#include <Robojax_L298N_DC_motor.h>

SoftwareSerial sw(2, 3); // RX, TX

int value;

#define LED 8   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#define BUZZER 13

#define ENA 10 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 4
#define IN2 5
//#define CHA 0

// motor 2 settings
#define IN3 6
#define IN4 7
#define ENB 11// this pin must be PWM enabled pin if Arduino board is used
//#define CHB 1

const int CCW = 2; // do not change
const int CW  = 1; // do not change

#define motor1 1 // do not change
#define motor2 2 // do not change



// for two motors without debug information // Watch video instruciton for this line: https://youtu.be/2JTMqURJTwg
Robojax_L298N_DC_motor robot(IN1, IN2, ENA, IN3, IN4, ENB);




void forward()
{

//  Serial.println("前进");
  robot.rotate(motor1, 70, CW);
  robot.rotate(motor2, 70, CW);
  delay(1000);
  stop1();
}
void back()
{

//  Serial.println("后退");
  robot.rotate(motor1, 70, CCW);
  robot.rotate(motor2, 70, CCW);
  delay(1000);
  stop1();
}
void left_forward()
{
//  Serial.println("左前");

  robot.brake(1);
  robot.rotate(motor2, 70, CW);
  delay(800);
  stop1();
  
}
void left_back()
{
//  Serial.println("左后");
  robot.brake(1);
  robot.rotate(motor2, 70, CCW);
  delay(800);
  stop1();
}
void right_forward()
{

//  Serial.println("右前");
  robot.brake(2);
  robot.rotate(motor1, 70, CW);
  delay(800);
  stop1();
}
void right_back()
{

//  Serial.println("右后");
  robot.brake(2);
  robot.rotate(motor1, 70, CCW);
  delay(800);
  stop1();
}

void stop1()
{
//  Serial.println("停止");
  robot.brake(1);
  robot.brake(2);
}

void setup() {
 Serial.begin(115200);
 Serial.println("Interfacfing arduino with esp32cam");
 sw.begin(115200);
 pinMode(LED, OUTPUT);
 digitalWrite(LED, HIGH);
 pinMode(BUZZER, OUTPUT);
 digitalWrite(BUZZER, LOW);
 robot.begin();
}

void loop() {
  if(sw.available()){
    value = sw.read();
    Serial.println("value:");
    Serial.println(value);  
//    if(value=='1'){
//      digitalWrite(ledPin, LOW);
//    }
//    if(value=='0'){
//      digitalWrite(ledPin, HIGH);
      switch(value){
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
          digitalWrite(LED, LOW);
          break;

        case '6':
          digitalWrite(LED, HIGH);
          break;

        case '5':
          digitalWrite(BUZZER, HIGH);
          delay(1000);
          digitalWrite(BUZZER, LOW);
          break;
    }
  }
}
