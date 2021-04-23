char val;
int INA = 4; //电机A正反转控制端
int PWMA = 5; //电机A调速端
int INB = 7; //电机B正反转控制端
int PWMB = 6; //电机B调速端
void setup()
{
  pinMode(INA,OUTPUT);
  pinMode(INB,OUTPUT);   //配置电机输出IO口为输出
  Serial.begin(9600);//打开串口并初始化设置波特率
  
}

void loop()
{
  val = Serial.read();

  if (-1 != val) {
    switch(val) 
    {
      case 'c':Serial.println("testOk");break;//pc端发送字符c，若返回testOk，说明连接正常
      case 'w':motosp(200,200);break; //按下w键，小车直行
      case 's':motosp(-200,-200);break; //按下s键，小车后退
      case 'q':motosp(100,200);break; //按下q键，向前左转
      case 'e':motosp(200,100);break; //按下e键，向前右转
      case 'a':motosp(-100,-200);break; //按下a键，向后左转
      case 'd':motosp(-200,-100);break; //按下d键，向后右转
     }
   delay(20);
  }
  else motosp(0,0);//未接收到数据时，小车停止

}
void motosp(int sp1,int sp2)//电机速度控制函数。括号内分别为左右电机速度值，
{
  if(sp1>0)                 //范围-255～+255，正值为正转，负值为反转。
  {
   digitalWrite(INA, HIGH);    
  }
  else
  {
   digitalWrite(INA, LOW); 
  }
  if(sp2>0)
  {
   digitalWrite(INB, HIGH); 
  }
  else
  {
   digitalWrite(INB, LOW); 
  }
  analogWrite(PWMA,abs (sp1)); 
  analogWrite(PWMB,abs (sp2));
}

