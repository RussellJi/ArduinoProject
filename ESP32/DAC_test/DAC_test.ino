void setup()
{

}

void loop()
{
   for(int i = 0 ; i<256; i++)
   {
    dacWrite(26,i);
    delay(10);
  }
}
