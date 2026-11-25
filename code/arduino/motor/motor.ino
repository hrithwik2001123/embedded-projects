int MIF=4;
int MIR=5;
void setup() {
 pinMode(MIF,OUTPUT);
 pinMode(MIR,OUTPUT);
}

void loop() {
  digitalWrite(MIF, HIGH);
  digitalWrite(MIR,LOW);
  delay(500);
  digitalWrite(MIF, LOW);
  digitalWrite(MIR,HIGH);
  delay(500);
}
