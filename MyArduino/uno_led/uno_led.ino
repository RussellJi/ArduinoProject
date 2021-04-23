#define IN4 7
#define IN3 6
#define IN1 4
#define IN2 5
#define ENA 10
void setup() {
  
//初始化各IO,模式为OUTPUT 输出模式
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(ENA, OUTPUT);
//  analogWrite(ENA, 170);
  digitalWrite(IN3, HIGH);
//  analogWrite(IN2, 255);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, HIGH);
//  analogWrite(ENA, 255);
//  digitalWrite(ENA,HIGH);
//默认电机停止转动，全部设为低电平  
  Serial.begin(9600);


}
void forward(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
}
void back(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}
void fast(){
  analogWrite(ENA, 225);
}
void low(){
  analogWrite(ENA, 100);
}
void stop(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
}
void loop() {
//      //forward 前进
//  uint8_t L_PWM = 0;
//  uint8_t R_PWM = 0;
//  bool L_DIR = 0;
//  bool R_DIR = 0;
//  L_PWM = 127;
//  R_PWM = 127;
//  L_DIR = 1;
//  R_DIR = 1;
//  analogWrite(IN3, L_PWM);
//  analogWrite(IN2, R_PWM);
//  digitalWrite(IN4, L_DIR);
//  digitalWrite(IN1, R_DIR);
//
//  analogWrite(IN2, 255);
//  delay(3000);
//  forward();
//  delay(3000);
//  fast();
//  delay(3000);
//  back();
//  delay(3000);
//  fast();
//  delay(3000);
//  stop();
//  
  delay(3000);
  digitalWrite(IN2, HIGH);
  
  digitalWrite(IN1, LOW);
  delay(3000);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN1, HIGH);
  delay(3000);
  digitalWrite(IN1 , LOW);
}
