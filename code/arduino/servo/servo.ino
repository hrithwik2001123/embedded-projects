#include <Servo.h>
Servo myservo;
int pos = 0;

void setup() 
{
  myservo.attach(9);
  Serial.begin(9600);
}

void loop()
{
  Serial.println("open");
  for(pos = 0; pos <= 180; pos++) {
    myservo.write(pos);
    delay(15);
  }

  delay(500); // Optional pause after opening

  Serial.println("close");
  for(pos = 180; pos >= 0; pos--) {
    myservo.write(pos);
    delay(15); 
  }

  delay(500); // Optional pause after closing
}
