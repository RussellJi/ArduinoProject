int SNUM[3] ;//定义3个传感器
int INA = 4; //电机A正反转控制端
int PWMA = 5; //电机A调速端
int INB = 7; //电机B正反转控制端
int PWMB = 6; //电机B调速端
void motospd(int sp1,int sp2);
void setup(){
pinMode(2, INPUT); //配置6个传感器IO口为输入
pinMode(3, INPUT); 
pinMode(8, INPUT); 
pinMode(11, INPUT); 
pinMode(12, INPUT); 
pinMode(13, INPUT); 
Serial.begin(9600); //打开串口设置波特率
pinMode(INA,OUTPUT);
pinMode(INB,OUTPUT);   //配置电机输出IO口为输出
}
void loop(){
 SNUM[0] = digitalRead(2);//SNUM[0]-SNUM[2]分别为从左到右三个红外寻线传感器
 SNUM[1] = digitalRead(3);
 SNUM[2] = digitalRead(8);
 for (int i=0;i<3;i++)
 {
   Serial.print(SNUM[i]);
  }
   Serial.println(SNUM[3]); //用串口依次输出6个传感器的值0或1

  if ((SNUM[0]==0)&&SNUM[1]&&SNUM[2])//左端传感器检测到黑线
  {
    motospd(50,120);//设置左右电机转速，使小车向左行驶
  }
  if (SNUM[0]&&(SNUM[1]==0)&&SNUM[2])//中间传感器检测到黑线
  {
    motospd(100,100);//小车直行
  }
  if (SNUM[0]&&SNUM[1]&&(SNUM[2]==0))//右端传感器检测到黑线
  {
    motospd(120,50);//小车向右行驶
  }    
   delay(50);
}
void motospd(int sp1,int sp2)//电机速度控制函数。括号内分别为左右电机速度值，
{
  if(sp1>0)                  //范围-255～+255，正值为正转，负值为反转。
    digitalWrite(INA, HIGH);    
  else
     digitalWrite(INA, LOW); 
  if(sp2>0)
     digitalWrite(INB, HIGH); 
  else
     digitalWrite(INB, LOW); 
  analogWrite(PWMA,abs (sp1)); 
  analogWrite(PWMB,abs (sp2));
}

