#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TANK_LOW_PIN   2
#define TANK_HALF_PIN  3
#define TANK_FULL_PIN  4
#define RELAY_PIN      5
String message;
// Debounce settings
#define DEBOUNCE_DELAY 50  // 50ms debounce delay
unsigned long lastDebounceTime = 0;
 static bool lastLow, lastHalf, lastFull;
  static bool stableLow, stableHalf, stableFull;
  
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
  delay(200); // Small delay to reduce LCD flicker
}

// --- Functions ---

void relayControl(bool state) {
  digitalWrite(RELAY_PIN, state ? HIGH : LOW); // Relay is active HIGH
}
void  check(){
// If FULL is active (regardless of others)
  if (stableFull == HIGH) {
    message = "Tank is Full";
    relayControl(false);
  }
  // If HALF is active (and FULL is not)
  else if (stableHalf == HIGH) {
    message = "Tank is Half";
    relayControl(false);
  }
  // If LOW is active (and FULL/HALF are not)
  else if (stableLow == HIGH) {
    message = "Tank is Low";
    relayControl(false);
  }
  // If none are active
  else {
    message = "Tank is Empty";
    relayControl(true);
  }
}

void monitorTank() {
 
  bool currentLow = digitalRead(TANK_LOW_PIN);
  bool currentHalf = digitalRead(TANK_HALF_PIN);
  bool currentFull = digitalRead(TANK_FULL_PIN);

  // Debounce logic (only update if stable for DEBOUNCE_DELAY)
  if (millis() - lastDebounceTime > DEBOUNCE_DELAY) {
    if (currentLow != lastLow) {
      stableLow = currentLow;
      lastLow = currentLow;
    }
    if (currentHalf != lastHalf) {
      stableHalf = currentHalf;
      lastHalf = currentHalf;
    }
    if (currentFull != lastFull) {
      stableFull = currentFull;
      lastFull = currentFull;
    }
    lastDebounceTime = millis();
  }

  

  // STRICT FULL CHECK (All 3 sensors must be LOW)
  if (stableFull == HIGH && stableHalf == HIGH && stableLow == HIGH) {
    message = "Tank is Full";
    relayControl(false);
  }
  else{
    check();
  }
  

  // Update LCD only if message changed
  if (message != lastMessage) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    lastMessage = message;
  }
}