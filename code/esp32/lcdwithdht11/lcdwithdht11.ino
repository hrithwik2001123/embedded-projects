#include <DHT.h>
#include <LiquidCrystal.h>

// LCD pin connections for ESP32 using different GPIO pins
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

#define DHTPIN 4        // DHT11 data pin connected to GPIO 4
#define DHTTYPE DHT11   // Sensor type DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);  // Start serial communication for debugging
  
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
    Serial.println("Failed to read from DHT sensor!");
    delay(1000);
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

  // Optional: Print to serial monitor for debugging
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%, Temperature: ");
  Serial.print(t);
  Serial.println("°C");

  delay(2000); // Update every 2s
}
