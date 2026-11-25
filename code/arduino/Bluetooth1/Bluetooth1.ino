#include <SoftwareSerial.h>

// ----- Bluetooth on D2 (RX), D3 (TX)
SoftwareSerial BT(2, 3);

// ----- Ultrasonic pins
#define TRIG_PIN 9
#define ECHO_PIN 10

// Read distance (cm). Returns -1 if no echo (timeout)
long readDistanceCM() {
  // Trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Echo with timeout (30 ms ≈ ~5 m max)
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (duration == 0) return -1;          // timeout / out of range

  // Convert to cm (sound speed ~343 m/s): cm = duration / 58
  long cm = (long)(duration / 58.0);
  return cm;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);   // PC Serial Monitor
  BT.begin(9600);       // HC-05 default data baud

  Serial.println("Ultrasonic -> Bluetooth started (9600 baud).");
  Serial.println("Sending distance every 500 ms...");
}

void loop() {
  long distance = readDistanceCM();

  if (distance < 0) {
    // No reading
    Serial.println("Distance: ---");
    BT.println("Distance: ---");
  } else {
    // Send to Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Send to Bluetooth app
    BT.print("Distance: ");
    BT.print(distance);
    BT.println(" cm");
  }

  delay(500);
}
