#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

// ===== RFID RC522 Setup =====
#define SS_PIN  5
#define RST_PIN 2
MFRC522 rfid(SS_PIN, RST_PIN);

// ===== LCD Setup =====
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===== Storage =====
#define MAX_LOGS 20   // store up to 20 scans
String scanLog[MAX_LOGS];
int logIndex = 0;

// ===== Known Cards =====
String getLabel(String uidHex) {
  if (uidHex == "00:E0:34:83") return "Snickers";
  if (uidHex == "D0:FA:2E:83") return "Fuse Chocolate";
  return "Unknown";
}

void setup() {
  Serial.begin(115200);
  SPI.begin(18, 19, 23);
  rfid.PCD_Init();

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID Ready...");
}

void loop() {
  // Check for card
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Build UID HEX string
  String uidHex = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uidHex += "0";
    uidHex += String(rfid.uid.uidByte[i], HEX);
    if (i != rfid.uid.size - 1) uidHex += ":";
  }
  uidHex.toUpperCase();

  // Find label
  String label = getLabel(uidHex);

  // Add to log
  if (logIndex < MAX_LOGS) {
    scanLog[logIndex] = uidHex + " - " + label;
    logIndex++;
  } else {
    Serial.println("⚠️ Log Full! Clear needed.");
  }

  // Print to Serial
  Serial.print("UID: "); Serial.println(uidHex);
  Serial.print("Label: "); Serial.println(label);

  // Show on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card:");
  lcd.setCursor(0, 1);
  lcd.print(label);

  // Wait until card removed
  while (rfid.PICC_IsNewCardPresent() || rfid.PICC_ReadCardSerial()) {
    delay(100);
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(200);
  
  // ===== Extra Feature: Clear logs if Serial input "C" =====
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'C' || cmd == 'c') {
      clearLogs();
    }
  }
}

void clearLogs() {
  for (int i = 0; i < MAX_LOGS; i++) {
    scanLog[i] = "";
  }
  logIndex = 0;
  Serial.println("✅ Logs cleared");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Logs Cleared!");
}
