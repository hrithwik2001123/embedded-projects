#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// ================= WIFI =================
const char* ssid = "DESKTOP";
const char* password = "123456789";

String server = "http://192.168.69.172:5000";

// ================= DHT =================
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ================= MOTOR =================
#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25

// ================= RELAYS =================
#define RELAY_SOIL 33
#define RELAY_DISEASE 32

// ================= SOIL =================
#define SOIL_PIN 34

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(RELAY_SOIL, OUTPUT);
  pinMode(RELAY_DISEASE, OUTPUT);
  // default OFF

  digitalWrite(RELAY_SOIL, LOW);
  digitalWrite(RELAY_DISEASE, LOW);

  stopMotor();

  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP IP: ");
  Serial.println(WiFi.localIP());
}

// ================= LOOP =================
void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    // ===== GET COMMAND =====
    HTTPClient http;
    http.begin(server + "/get_command");

    int code = http.GET();
    String cmd = "stop";

    if (code > 0) {
      cmd = http.getString();
      cmd.trim();

      Serial.print(" CMD: ");
      Serial.println(cmd);
    } else {
      Serial.print("❌ HTTP ERROR: ");
      Serial.println(code);
    }

    http.end();

    // ===== EXECUTE =====
    executeCommand(cmd);

    // ===== SENSOR =====
    sendSensor();
  }

  delay(500);  // faster loop
}

// ================= SENSOR =================
void sendSensor() {

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int soil = analogRead(SOIL_PIN);

  // ===== FIX DHT (USE LAST VALUE) =====
  static float lastT = 0;
  static float lastH = 0;

  if (!isnan(t) && !isnan(h)) {
    lastT = t;
    lastH = h;
  } else {
    Serial.println("⚠️ DHT retry (using last value)");
  }

  t = lastT;
  h = lastH;

  Serial.println("Temp: " + String(t));
  Serial.println("Hum: " + String(h));
  Serial.println("Soil: " + String(soil));

  HTTPClient http;
  http.begin(server + "/update");
  http.addHeader("Content-Type", "application/json");

  String json = "{";
  json += "\"temp\":" + String(t) + ",";
  json += "\"hum\":" + String(h) + ",";
  json += "\"soil\":" + String(soil);
  json += "}";

  int code = http.POST(json);

  Serial.print("POST STATUS: ");
  Serial.println(code);

  http.end();
}

// ================= COMMAND =================
void executeCommand(String cmd) {

  if (cmd == "forward") {
    Serial.println("FORWARD");
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  }
  else if (cmd == "backward") {
    Serial.println("BACKWARD");
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  }
  else if (cmd == "left") {
    Serial.println("LEFT");
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  }
  else if (cmd == "right") {
    Serial.println("RIGHT");
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  }
  else if (cmd == "soil_on") {
    Serial.println("SOIL RELAY");
    digitalWrite(RELAY_SOIL, HIGH);
    delay(500);
     digitalWrite(RELAY_SOIL, LOW);
  }
  else if (cmd == "disease_on") {
    Serial.println("🦠 DISEASE RELAY");
    digitalWrite(RELAY_DISEASE, HIGH);
    delay(500);
    digitalWrite(RELAY_DISEASE, LOW);
  }else if (cmd == "disease_off"){
    digitalWrite(RELAY_DISEASE, LOW);
  }
  else if (cmd == "soil_off"){
    digitalWrite(RELAY_SOIL, LOW);
  }
  else {
    Serial.println("⏹️ STOP");
    stopMotor();
  }
}


// ================= STOP =================
void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
