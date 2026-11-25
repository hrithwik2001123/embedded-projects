int MIF=2;
int MIR=3;
int MIF1=4;
int MIR1=5;
void setup()
{
  Serial.begin(9600);
  pinMode(MIF,OUTPUT);
  pinMode(MIR,OUTPUT);
  digitalWrite(MIF, LOW);
  digitalWrite(MIR,LOW);
  pinMode(MIF1,OUTPUT);
  pinMode(MIR1,OUTPUT);
  digitalWrite(MIF1, LOW);
  digitalWrite(MIR1,LOW);
}
void loop()
{
  if (Serial.available())
  {
    char msg = Serial.read();
    if (msg == 'F')
    {
       digitalWrite(MIF, HIGH);
       digitalWrite(MIR,LOW);
       digitalWrite(MIF1, HIGH);
       digitalWrite(MIR1,LOW);
       delay(500);
    }
    if (msg == 'B')
    {
       digitalWrite(MIF, LOW);
       digitalWrite(MIR,HIGH);
       digitalWrite(MIF1, LOW);
       digitalWrite(MIR1,HIGH);
       delay(500);
    }
    if (msg == 'C')
    {
      digitalWrite(MIF, LOW);
      digitalWrite(MIR,LOW);
      digitalWrite(MIF1, LOW);
      digitalWrite(MIR1,LOW); 
      } 
    
  }
}
