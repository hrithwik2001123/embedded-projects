int flamePin = 2;  
int buzzerPin = 8; 

void setup() {
  pinMode(flamePin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(flamePin);

  if (sensorValue == LOW) {  
    digitalWrite(buzzerPin, HIGH);
    Serial.println(" Flame Detected!");
  } else {
    digitalWrite(buzzerPin, LOW);
    Serial.println("No Flame");
  }

  delay(200);
}
