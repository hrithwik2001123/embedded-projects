int MIF=2;
int MIR=3;
void setup()
{
  Serial.begin(9600);
  pinMode(MIF,OUTPUT);
  pinMode(MIR,OUTPUT);
  digitalWrite(MIF, LOW);
  digitalWrite(MIR,LOW);
}
void loop()
{
  if (Serial.available())
  {
    char msg = Serial.read();
    if (msg == 'A')
    {
       digitalWrite(MIF, HIGH);
       digitalWrite(MIR,LOW);
       delay(500);
    }
    if (msg == 'B')
    {
       digitalWrite(MIF, LOW);
       digitalWrite(MIR,HIGH);
       delay(500);
    }
    if (msg == 'C')
    {
      digitalWrite(MIF, LOW);
      digitalWrite(MIR,LOW);    } 
    
  }
}
