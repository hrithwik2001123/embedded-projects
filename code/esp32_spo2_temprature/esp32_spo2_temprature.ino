#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HTTPClient.h>
#include <WiFi.h>

// ================= Pins =================
#define ONE_WIRE_BUS 4       // DS18B20 on GPIO4
#define REPORTING_PERIOD_MS 1000
// SDA = 21, SCL = 22

// ================= Objects =================
PulseOximeter pox;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

uint32_t tsLastReport = 0;
unsigned long tempRequestTime = 0;
bool waitingForTemp = false;
float temperature = 0;

// ================= WiFi =================
const char* ssid     = "DESKTOP-LLIVSRG 6797";
const char* password = "12345678";
const char* serverName = "http://192.168.29.254:5000/test";

// ================= Averaging Filter =================
#define AVG_COUNT 5
float hrBuffer[AVG_COUNT], spo2Buffer[AVG_COUNT];
int avgIndex = 0;

float avg(float *arr, int size) {
  float sum = 0;
  for (int i = 0; i < size; i++) sum += arr[i];
  return sum / size;
}

// ================= WiFi Setup =================
void setup_wifi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ");
  Serial.println(ssid);

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nCONNECTED");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect WiFi!");
  }
}

// ================= Send Data =================
void send_data(float heart, float spo2, float temperature) {
  if(WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"heart\":" + String(heart, 1) +
                      ",\"oxygen\":" + String(spo2, 1) +
                      ",\"temperature\":" + String(temperature, 1) + "}";

    int httpResponseCode = http.POST(jsonData);
    Serial.print("HTTP Response: ");
    Serial.println(httpResponseCode);

    if(httpResponseCode > 0) {
      String res = http.getString();
      Serial.println("Server reply: " + res);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}

// ================= Beat Callback =================
void onBeatDetected() {
  Serial.println("Beat!");
}

// ================= Setup =================
void setup() {
  Serial.begin(115200);
  setup_wifi();

  // SpO2 init
  if (!pox.begin()) {
    Serial.println("FAILED to init SpO2 sensor");
    for (;;);
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);

  // DS18B20 init
  sensors.begin();
  sensors.setResolution(12);
  sensors.setWaitForConversion(false);

  // Init averaging buffers
  for (int i = 0; i < AVG_COUNT; i++) {
    hrBuffer[i] = 0;
    spo2Buffer[i] = 0;
  }
}

// ================= Loop =================
void loop() {
  pox.update();  // keep updating sensor

  unsigned long now = millis();

  // Handle DS18B20 async
  if (!waitingForTemp) {
    sensors.requestTemperatures();
    tempRequestTime = now;
    waitingForTemp = true;
  }
  else if (waitingForTemp && now - tempRequestTime > 750) {
    temperature = sensors.getTempCByIndex(0);
    waitingForTemp = false;
  }

  // Every second
  if (now - tsLastReport > REPORTING_PERIOD_MS) {
    tsLastReport = now;

    // Get values
    float hr = pox.getHeartRate();
    float spo2 = pox.getSpO2();

    // Add to averaging buffer
    hrBuffer[avgIndex] = hr;
    spo2Buffer[avgIndex] = spo2;
    avgIndex = (avgIndex + 1) % AVG_COUNT;

    float hrAvg = avg(hrBuffer, AVG_COUNT);
    float spo2Avg = avg(spo2Buffer, AVG_COUNT);

    Serial.print("Heart rate: ");
    Serial.print(hrAvg);
    Serial.print(" bpm / SpO2: ");
    Serial.print(spo2Avg);
    Serial.print(" % / Temp: ");
    Serial.println(temperature);

    // ✅ Only send if stable
    if (hrAvg > 30 && spo2Avg > 70 && temperature > -20) {
      send_data(hrAvg, spo2Avg, temperature);
    } else {
      Serial.println("⚠️ Waiting for stable sensor data...");
    }
  }
}
