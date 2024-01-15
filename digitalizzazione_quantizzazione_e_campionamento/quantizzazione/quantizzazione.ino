void setup() {
  Serial.begin(115200);

}

void loop() {
  int d = analogRead(A0);
  Serial.print(d);
  Serial.print("   ");
  Serial.println((float)d/1023.0*4.99);
  delay(1000);
}
