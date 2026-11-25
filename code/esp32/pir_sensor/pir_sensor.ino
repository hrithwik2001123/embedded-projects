// ===== PIR Motion Sensor with ESP32 Onboard LED =====

#define PIR_PIN  27        // PIR sensor output pin
#define LED_PIN  2         // ESP32 onboard LED (GPIO2 on most dev boards)

void setup() {
  pinMode(PIR_PIN, INPUT_PULLDOWN); // Use pulldown to avoid floating input
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("PIR Motion Sensor with ESP32 Initialized...");
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    digitalWrite(LED_PIN, HIGH);   // Turn LED ON
    Serial.println("Motion detected!");
  } else {
    digitalWrite(LED_PIN, LOW);    // Turn LED OFF
    Serial.println("No motion...");
  }

  delay(200);  // Small delay
}
