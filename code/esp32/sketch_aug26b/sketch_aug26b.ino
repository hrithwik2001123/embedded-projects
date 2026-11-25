int irPin = 13;   // IR sensor OUT pin connected to Arduino D2
int ledPin = 2; // Built-in LED for testing

void setup() {
  pinMode(irPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(irPin);

  if (sensorValue == LOW) {  
    // LOW means object detected for most IR sensors
    digitalWrite(ledPin, HIGH);
    Serial.println("Object Detected!");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("No Object");
  }

  delay(200);
}
