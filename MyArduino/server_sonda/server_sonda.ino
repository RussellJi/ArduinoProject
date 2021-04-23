#include <Servo.h>       
#define ServoPin 12      //定义舵机连接到12号引脚
#define LED 13           //定义LED为13号引脚
#define sonar_Echo_Pin 8 //定义超声波传感器Echo的引脚为8号口
#define sonar_Trig_Pin 9 //定义超声波传感器Trig的引脚为9号口

float left_distance;  //定义一个变量存储左边的距离
float right_distance; //定义一个变量存储右边的距离

Servo myservo; //声明一个对象名为myservo

float sonar_detection() //超声波测距函数
{
  float distance;                    //定义一个变量存储测得的距离
  digitalWrite(sonar_Trig_Pin, LOW); //产生一个10us的脉冲去触发Trig_Pin
  delayMicroseconds(2);
  digitalWrite(LED, 1);
  digitalWrite(sonar_Trig_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonar_Trig_Pin, LOW);
  digitalWrite(LED, 0);
  distance = pulseIn(sonar_Echo_Pin, HIGH, 8000) / 58.00; //检测脉冲宽度，并计算距离值
  if (distance >= 130 || distance == 0)                   //判断如果距离大于等于130cm或者等于0，则让距离等于130
  {
    distance = 130;
  }

  Serial.print(distance); //串口输出距离值
  Serial.print("cm");     //串口输出距离值单位
  Serial.println();       //换行
  delay(5);               //延时5秒

  return distance; //返回距离值
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);    //打开串口设置波特率
  pinMode(sonar_Trig_Pin, OUTPUT); //配置Trig端口为输出模式
  pinMode(sonar_Echo_Pin, INPUT);  //配置Echo端口为输入模式
  myservo.attach(ServoPin); //初始化舵机对象连接的引脚
  myservo.write(180);       //left
  delay(500);
  myservo.write(0); //right
  delay(500);
  myservo.write(73); //positive
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = sonar_detection();
  Serial.println(sonar_detection());
  if(distance<20){
    myservo.write(180);       //left
  }else if(distance<40){
    myservo.write(0);
  }else{
     myservo.write(73);
  }
  
}
