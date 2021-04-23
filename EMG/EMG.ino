// reads analog input from the five inputs from your arduino board 
// and sends it out via serial

// variables for input pins and
int analogInput[6] = {A0, A1, A2, A3, A4, A5};
  
// variable to store the value 
int value[6] = {0, 0, 0, 0, 0, 0};  
 
void setup()
{
  // declaration of pin modes
  for(int i=0;i<6;i++)
    pinMode(analogInput[i], INPUT);    

  
  // begin sending over serial port
  Serial.begin(9600);
}

void loop()
{
  // read the value on analog input
  for(int i=0;i<6;i++)
  {
    value[i] = analogRead(analogInput[i]);
  }
  Serial.print(value[0]);Serial.print(",");
  Serial.print(value[1]);Serial.print(",");
  Serial.print(value[2]);Serial.print(",");
  Serial.print(value[3]);Serial.print(",");
  Serial.print(value[4]);Serial.print(",");
  Serial.println(value[5]);
  // print out value over the serial port
  delay(10);
}
