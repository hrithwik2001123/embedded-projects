#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TANK_LOW_PIN    2
#define TANK_HALF_PIN   3
#define TANK_FULL_PIN   4
#define RELAY_PIN       5
#define MOTOR_LED_PIN   6

String lastMessage = "";
bool motorRunning = false;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(TANK_LOW_PIN, INPUT_PULLUP);
  pinMode(TANK_HALF_PIN, INPUT_PULLUP);
  pinMode(TANK_FULL_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(MOTOR_LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW); // Start with motor OFF
  digitalWrite(MOTOR_LED_PIN, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Tank Monitor");
  lcd.setCursor(0, 1);
  lcd.print(" Ready...");
  delay(1500);
  lcd.clear();
}

void loop() {
  monitorTank();
  delay(200); // Prevent flickering
}

void monitorTank() {
  bool low  = digitalRead(TANK_LOW_PIN);
  bool half = digitalRead(TANK_HALF_PIN);
  bool full = digitalRead(TANK_FULL_PIN);

  if (full == LOW) {
    // Tank is full - turn off motor if it was running
    if (motorRunning) {
      showStatus("Tank is Full", false);
      motorRunning = false;
    } else {
      showStatus("Tank is Full", false);
    }
  } 
  else if (half == LOW) {
    // Just show status, don't change motor state
    if (motorRunning) {
      showStatus("Tank is Half", true);
    } else {
      showStatus("Tank is Half", false);
    }
  } 
  else if (low == LOW) {
    // Tank is low - turn on motor if not already running
    if (!motorRunning) {
      showStatus("Tank is Low", true);
      motorRunning = true;
    } else {
      showStatus("Tank is Low", true);
    }
  } 
  else {
    // Tank is empty - turn on motor if not already running
    if (!motorRunning) {
      showStatus("Tank Empty", true);
      motorRunning = true;
    } else {
      showStatus("Tank Empty", true);
    }
  }
}

void showStatus(String tankMessage, bool motorOn) {
  if (tankMessage != lastMessage || motorOn != digitalRead(RELAY_PIN)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(tankMessage);

    lcd.setCursor(0, 1);
    if (motorOn) {
      lcd.print("Motor ON");
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(MOTOR_LED_PIN, HIGH);
    } else {
      lcd.print("Motor OFF");
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(MOTOR_LED_PIN, LOW);
    }

    lastMessage = tankMessage;
  }
}