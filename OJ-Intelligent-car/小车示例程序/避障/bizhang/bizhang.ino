int SNUM[3] ;//定义3个传感器，从SNUM[0]-SNUM[2]为从左到右3个红外避障传感器
int INA = 4; //电机A正反转控制端
int PWMA = 5; //电机A调速端
int INB = 7; //电机B正反转控制端
int PWMB = 6; //电机B调速端

void motospd(int sp1,int sp2) //电机速度控制函数。括号内分别为左右电机速度值，
{                        //范围-255～+255，正值为正转，负值为反转。
  if(sp1>0)
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
void setup(){

pinMode(11, INPUT); //配置左传感器IO口为输入
pinMode(12, INPUT); //配置中传感器IO口为输入
pinMode(13, INPUT); //配置右传感器IO口为输入
Serial.begin(9600); //打开串口，初始化
pinMode(INA,OUTPUT);
pinMode(INB,OUTPUT);   //配置电机驱动IO口为输出

}
void loop(){

SNUM[0] = digitalRead(11);//左传感器赋值
 SNUM[1] = digitalRead(12); //中传感器赋值
 SNUM[2] = digitalRead(13); //右传感器赋值
 for (int i=0;i<3;i++)
 {
   Serial.print(SNUM[i]);//串口输出每个传感器的值，打开串口可显示传感器检测结果
  }                  
   Serial.println(SNUM[2]); 
  if ((SNUM[0]==1)&&(SNUM[1]==1)&&(SNUM[2]==1))//所有传感器都没有检测到障碍
motospd(100,100);                          //直行
  if ((SNUM[0]==0)&&(SNUM[1]==1)&&(SNUM[2]==1)) //左传感器检测到障碍物
    motospd(100,50);                           //右转
    if ((SNUM[0]==1)&&(SNUM[1]==1)&&(SNUM[2]==0)) //右传感器检测到障碍物
    motospd(50,100);                             //左转
    if ((SNUM[0]==1)&&(SNUM[1]==0)&&(SNUM[2]==1)) //中传感器检测到障碍物
    motospd(-100,-100);                           //后退
delay(50);
}

