#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD: I2C Address 0x27, 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sensor and control pins
#define TANK_LOW_PIN   2
#define TANK_HALF_PIN  3
#define TANK_FULL_PIN  4
#define RELAY_PIN      5

String lastMessage = "";

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(TANK_LOW_PIN, INPUT_PULLUP);
  pinMode(TANK_HALF_PIN, INPUT_PULLUP);
  pinMode(TANK_FULL_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Tank Monitor");
  lcd.setCursor(0, 1);
  lcd.print(" Ready...");
  delay(1500);
  lcd.clear();

  relayControl(false); // Start with relay off
}

void loop() {
  monitorTank();
  delay(200); // Small delay to avoid flickering
}

// --- Functions ---

void monitorTank() {
  bool low  = digitalRead(TANK_LOW_PIN);
  bool half = digitalRead(TANK_HALF_PIN);
  bool full = digitalRead(TANK_FULL_PIN);

  String message;

  if (full == LOW) {
    message = "Tank is Full";
    relayControl(false); // Turn OFF relay
  } else if (half == LOW) {
    message = "Tank is Half";
    relayControl(false); // Turn OFF relay
  } else if (low == LOW) {
    message = "Tank is Low";
    relayControl(false); // Turn OFF relay
  } else {
    message = "Tank is Empty";
    relayControl(true);  // Turn ON relay
  }

  if (message != lastMessage) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    lastMessage = message;
  }
}

void relayControl(bool state) {
  digitalWrite(RELAY_PIN, state ? HIGH : LOW); // Relay is active HIGH
}
