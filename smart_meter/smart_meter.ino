#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal.h>
#include <math.h>

// ================== LCD PINS ==================
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

// ================== SENSOR PINS ==================
const int zmptPin = 34;     // Voltage sensor
const int acsPin  = 33;     // Current sensor
const int hallPin = 35;     // Hall sensor
const int relayPin = 23;    // Safe GPIO for relay

// ================== WIFI ==================
const char* ssid = "DESKTOP";
const char* password = "123456789";

// ================== SERVER ==================
const char* dataURL = "http://192.168.29.7:5000/data";
const char* commandURL = "http://192.168.29.7:5000/get_command";

const String consumerNum = "CN-998877";

// ================== CALIBRATION ==================
float voltageCal = 309.6;
float currentCal = 0.646;

const float vRef = 3.3;
const int adcMax = 4095;

// ================== RMS FUNCTION ==================
float getRMS(int pin) {

  float offset = 0;
  float sumSq = 0;

  // Find offset
  for (int i = 0; i < 300; i++)
    offset += analogRead(pin);

  offset /= 300.0;

  // RMS sampling
  for (int i = 0; i < 1500; i++) {
    float adc = analogRead(pin) - offset;
    float voltage = (adc * vRef) / adcMax;
    sumSq += voltage * voltage;
    delayMicroseconds(100);
  }

  return sqrt(sumSq / 1500);
}

// ================== SEND DATA ==================
void sendData(float voltage, float current, bool magnet) {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin(dataURL);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"consumer_number\":\"" + consumerNum + "\",";
    json += "\"voltage\":" + String(voltage, 2) + ",";
    json += "\"ampere\":" + String(current, 3) + ",";
    json += "\"halleffect\":\"" + String(magnet ? "DETECTED" : "NONE") + "\"";
    json += "}";

    Serial.println("\n--- Sending Data ---");
    Serial.println(json);

    int httpCode = http.POST(json);

    if (httpCode > 0) {
      Serial.printf("HTTP Response Code: %d\n", httpCode);
      String response = http.getString();
      Serial.println("Server Response: " + response);
    } else {
      Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}

// ================== GET RELAY COMMAND ==================
void getRelayCommand() {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin(commandURL);

    int httpCode = http.GET();

    if (httpCode > 0) {

      String payload = http.getString();
      Serial.println("Command: " + payload);

      if (payload.indexOf("ON") > 0) {
        digitalWrite(relayPin, HIGH);    // Active LOW relay
        Serial.println("Relay ON");
      }
      else if (payload.indexOf("OFF") > 0) {
        digitalWrite(relayPin, LOW);
        Serial.println("Relay OFF");
      }

    } else {
      Serial.println("Command fetch failed");
    }

    http.end();
  }
}

// ================== SETUP ==================
void setup() {

  Serial.begin(115200);

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  pinMode(hallPin, INPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, HIGH);   // Relay OFF initially

  lcd.begin(16, 2);
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1500);
}

// ================== LOOP ==================
void loop() {

  float vRaw = getRMS(zmptPin);
  float iRaw = getRMS(acsPin);

  float voltage = vRaw * voltageCal;
  float current = (iRaw / 0.066) * currentCal;

  if (current < 0.08)
    current = 0;

  bool magnet = (digitalRead(hallPin) == LOW);

  // Send data to server
  sendData(voltage, current, magnet);

  // Get relay command from server
  getRelayCommand();

  // LCD Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(voltage, 1);
  lcd.print(" A:");
  lcd.print(current, 2);

  lcd.setCursor(0, 1);
  lcd.print("Hall:");
  lcd.print(magnet ? "YES" : "NO");

  delay(5000);   // 5 seconds interval
}
