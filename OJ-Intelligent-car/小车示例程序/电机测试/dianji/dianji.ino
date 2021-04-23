/*电机测试程序
功能：测试电机驱动功能和电机连线是否正确
效果：左电机反转，右电机正转，电机转速由小到大。
*/
int INA = 4; //电机A正反转控制端
int PWMA = 5; //电机A调速端
int INB = 7; //电机B正反转控制端
int PWMB = 6; //电机B调速端
void setup(){
pinMode(INA,OUTPUT);
pinMode(INB,OUTPUT);   //配置电机输出IO口为输出
}
void loop(){
 int value;
 for(value = 20 ; value <= 255; value+=2){    //循环每次速度增加2最大到255
 motosp(-value,value);//电机速度赋值，左电机负值为反转，右电机正转。
 delay(50);
 }
}
void motosp(int sp1,int sp2)//声明电机速度控制函数。括号内定义的变量分别为左右电机速
//度值，范围-255～+255，正值为正转，负值为反转。
{
  if(sp1>0) {
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

