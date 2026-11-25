#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IWatchdog.h>

// LCD setup (16x2 display with I2C address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sensor pins - using pull-up resistors
#define LOW_PIN PB1
#define MID_PIN PB2
#define HIGH_PIN PB10

// Watchdog timeout (4 seconds)
#define WATCHDOG_TIMEOUT 4000000

void setup() {
  // Configure pins with internal pull-up resistors
  pinMode(LOW_PIN, INPUT_PULLUP);
  pinMode(MID_PIN, INPUT_PULLUP);
  pinMode(HIGH_PIN, INPUT_PULLUP);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Starting System...");
  
  // Initialize Watchdog timer
  IWatchdog.begin(WATCHDOG_TIMEOUT);
  
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read sensors (inverted because we're using pull-ups)
  bool lowActive = !digitalRead(LOW_PIN);
  bool midActive = !digitalRead(MID_PIN);
  bool highActive = !digitalRead(HIGH_PIN);

  lcd.clear();
  lcd.setCursor(0, 0);
  
  // Determine water level state
  if (!lowActive && !midActive && !highActive) {
    lcd.print("Tank EMPTY");
  }
  else if (lowActive && !midActive && !highActive) {
    lcd.print("LOW Level");
  }
  else if (lowActive && midActive && !highActive) {
    lcd.print("MID Level");
  }
  else if (lowActive && midActive && highActive) {
    lcd.print("FULL Level");
  }
  else {
    // Handle unexpected sensor combinations
    lcd.print("SENSOR ERROR");
    lcd.setCursor(0, 1);
    lcd.print("L:");
    lcd.print(lowActive);
    lcd.print(" M:");
    lcd.print(midActive);
    lcd.print(" H:");
    lcd.print(highActive);
  }

  // Reset watchdog timer
  IWatchdog.reload();
  
  delay(500); // Update every 0.5 seconds
}