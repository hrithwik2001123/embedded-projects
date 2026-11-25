#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <LiquidCrystal.h>

// ---------- LCD Configuration (4-bit parallel) ----------
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

// ---------- WiFi Credentials ----------
const char* ssid = "redmi";
const char* password = "redmi123";

// ---------- ThingSpeak ----------
String apiKey = "ERCQB3LJOAB455AQ";
String serverURL = "http://api.thingspeak.com/update?api_key=" + apiKey;

// ---------- DHT11 Configuration ----------
#define DHTPIN 4        // DHT11 data pin connected to GPIO 4
#define DHTTYPE DHT11   // Sensor type DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---------- Timing ----------
unsigned long lastTime = 0;
unsigned long lastLCDUpdate = 0;
const unsigned long thingSpeakDelay = 30000; // 30 seconds
const unsigned long lcdDelay = 2000;         // 2 seconds

WiFiClient client;
HTTPClient http;

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Initializing...");

  // Initialize DHT sensor
  dht.begin();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  lcd.setCursor(0, 1);
  lcd.print("WiFi connecting");

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.println("IP address: " + WiFi.localIP().toString());

  lcd.clear();
  lcd.print("WiFi Connected!");
  delay(2000);
  lcd.clear();
}

// ---------- Main Loop ----------
void loop() {
  // Update LCD every 2 seconds
  if (millis() - lastLCDUpdate >= lcdDelay) {
    updateLCD();
    lastLCDUpdate = millis();
  }

  // Send to ThingSpeak every 30 seconds
  if (millis() - lastTime >= thingSpeakDelay) {
    sendToThingSpeak();
    lastTime = millis();
  }
}

// ---------- Update LCD Display ----------
void updateLCD() {
  // Read DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  // Check if DHT sensor readings failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    humidity = 0.0;
    temperature = 0.0;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature, 1);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humi:");
  lcd.print(humidity, 1);
  lcd.print("%");

  // Print to Serial for debugging
  Serial.print(temperature, 1);
  Serial.print("C | H: ");
  Serial.print(humidity, 1);
  Serial.println("%");
}

// ---------- Send Data to ThingSpeak ----------
void sendToThingSpeak() {
  // Read sensors again
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if DHT sensor readings failed
  if (isnan(humidity) || isnan(temperature)) {
    humidity = 0.0;
    temperature = 0.0;
  }

  Serial.print("Sending to ThingSpeak - ");
  Serial.print(temperature, 1);
  Serial.print("C, H: ");
  Serial.print(humidity, 1);
  Serial.println("%");

  // Send to ThingSpeak if WiFi connected
  if (WiFi.status() == WL_CONNECTED) {
    String requestURL = serverURL +
                        "&field1=" + String(temperature, 1) +
                        "&field2=" + String(humidity, 1);

    http.begin(client, requestURL);
    int responseCode = http.GET();

    if (responseCode > 0) {
      Serial.print("ThingSpeak Response code: ");
      Serial.println(responseCode);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sent to TS!");
      lcd.setCursor(0, 1);
      lcd.print("Code:");
      lcd.print(responseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(responseCode);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TS Error!");
      lcd.setCursor(0, 1);
      lcd.print("Code:");
      lcd.print(responseCode);
    }

    http.end();
    delay(2000);
    lcd.clear();
  } else {
    Serial.println("WiFi Disconnected");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Error!");
    delay(2000);
    lcd.clear();

    // Reconnect WiFi
    WiFi.begin(ssid, password);
  }
}
