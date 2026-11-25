
int relayPin = 7; 

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT); 
}
void loop()
{
  if (Serial.available())
  {
    char msg = Serial.read();
    if (msg == 'A')
    {
      digitalWrite(relayPin, HIGH);
    }
    if (msg == 'B')
    {
      digitalWrite(relayPin, LOW);
    }
   
  }
}
