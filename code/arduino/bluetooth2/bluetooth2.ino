int led1=2;
int led2=3;
void setup()
{
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}
void loop()
{
  if (Serial.available())
  {
    char msg = Serial.read();
    if (msg == 'A')
    {
      digitalWrite(led1, HIGH);
    }
    if (msg == 'B')
    {
      digitalWrite(led2, HIGH);
    }
    if (msg == 'C')
    {
      digitalWrite(led1, LOW);
    } 
    if (msg == 'D')
    {
      digitalWrite(led2, LOW);
    }
  }
}