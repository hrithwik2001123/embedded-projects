#include <DHT.h>
#include <LiquidCrystal.h>

// LCD pin connections: RS=2, E=3, D4=4, D5=5, D6=6, D7=7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define DHTPIN 8        // DHT11 data pin connected to Arduino pin 8
#define DHTTYPE DHT11   // Sensor type DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);         // Initialize 16x2 LCD
  dht.begin();              // Start DHT sensor
  lcd.print("DHT11 Sensor"); // Intro message
  delay(2000);
  lcd.clear();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Celsius

  if (isnan(h) || isnan(t)) { // Check if sensor failed
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error  ");
    return;
  }

  // Print Humidity on 1st line
  lcd.setCursor(0, 0);
  lcd.print("H: ");
  lcd.print(h);
  lcd.print("%   "); // extra spaces to clear old chars

  // Print Temperature on 2nd line
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(t);
  lcd.print("C   ");

  delay(2000); // Update every 2s
}
