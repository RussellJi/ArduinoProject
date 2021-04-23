#define PIN_LED 5
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_LED,HIGH);
  delay(3000);
  digitalWrite(PIN_LED,LOW);
  delay(3000);
}
