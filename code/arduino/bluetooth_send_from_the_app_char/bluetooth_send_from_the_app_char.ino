#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3); // RX = D2, TX = D3

void setup() {
  Serial.begin(9600);    // USB serial
  BT.begin(9600);        // SoftwareSerial
  Serial.println("Loopback test on pins 2 & 3. Type something...");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    BT.write(c);         // what you type goes out TX (D3)
  }
  if (BT.available()) {
    char c = BT.read();  // comes back into RX (D2)
    Serial.write(c);     // echoed to Serial Monitor
  }
}
