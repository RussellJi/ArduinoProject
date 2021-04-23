int SNUM[6] ;
int INA = 4; //电机A正反转控制端
int PWMA = 5; //电机A调速端
int INB = 7; //电机B正反转控制端
int PWMB = 6; //电机B调速端

void motospd(int sp1,int sp2)
{
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

pinMode(2, INPUT); 
pinMode(3, INPUT); 
pinMode(8, INPUT); 
pinMode(11, INPUT); 
pinMode(12, INPUT); 
pinMode(13, INPUT); 
Serial.begin(9600); 
pinMode(INA,OUTPUT);
pinMode(INB,OUTPUT);   //配置电机输出IO口为输出

}
void loop(){

 SNUM[0] = digitalRead(2);
 SNUM[1] = digitalRead(3);
 SNUM[2] = digitalRead(8);
 SNUM[3] = digitalRead(11);
 SNUM[4] = digitalRead(12);
 SNUM[5] = digitalRead(13);
 for (int i=0;i<5;i++)
 {
   Serial.print(SNUM[i]);
  }
   Serial.println(SNUM[5]); 

  if ((SNUM[0]==0)&&SNUM[1]&&SNUM[2])
  {
    motospd(50,100);
  }
  if (SNUM[0]&&(SNUM[1]==0)&&SNUM[2])
  {
    motospd(100,100);
  }
  if (SNUM[0]&&SNUM[1]&&(SNUM[2]==0))
  {
    motospd(100,50);
  }
    if ((SNUM[3]==0)||(SNUM[4]==0)||(SNUM[5]==0))
      motospd(-100,-100);
    
   delay(50);
}
