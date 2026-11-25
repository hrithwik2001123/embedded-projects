int MQ = 2;  
int buzzerPin = 8; 

void setup() {
  pinMode(MQ, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(MQ);

  if (sensorValue == LOW) {  
    digitalWrite(buzzerPin, HIGH);
    Serial.println(" value");
  } else {
    digitalWrite(buzzerPin, LOW);
    Serial.println("no value");
  }

  delay(200);
}
