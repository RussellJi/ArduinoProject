
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, INPUT);
}






void loop() {
  // put your main code here, to run repeatedly:
  double val = analogRead(A0);
  Serial.println(val);
//  int buttonState = digitalRead(4);
//   print out the state of the button:
//  Serial.println(buttonState);
}
