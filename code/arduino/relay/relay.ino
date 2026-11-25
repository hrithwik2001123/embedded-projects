
int relayPin = 7; 

void setup() {
  pinMode(relayPin, OUTPUT); 
}
void loop() {
  digitalWrite(relayPin, LOW); 
  delay(2000); 
  digitalWrite(relayPin, HIGH); 
  delay(2000); 
}
