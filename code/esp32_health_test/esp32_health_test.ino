/* ESP32 FreeRTOS example:
   - High priority task reads MAX30100 continuously (pox.update())
   - Lower priority task reads DS18B20 every 1s
   - Network task posts combined data to Flask
*/

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <HTTPClient.h>

// -------- WiFi / Server --------
const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASS";
const char* serverName = "http://192.168.29.253:5000/test";

// -------- MAX30100 --------
PulseOximeter pox;
volatile bool newPoxReading = false; // flag set when new valid reading available

// -------- DS18B20 --------
#define ONE_WIRE_BUS 4    // change if you use different pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// -------- Shared data + mutex --------
struct SensorData {
  float heartRate;
  float spO2;
  float temperature;
  unsigned long timestamp;
};

SensorData latest = {0,0,0,0};
SemaphoreHandle_t xDataMutex;

// -------- Task handles (optional) --------
TaskHandle_t taskMaxHandle = NULL;
TaskHandle_t taskTempHandle = NULL;
TaskHandle_t taskNetHandle = NULL;

// ---------- Utility: set when beat detected ----------
void onBeatDetected() {
  // optional debug: Serial.println("Beat!");
}

// ---------- MAX30100 Task (High priority) ----------
void Task_MAX30100( void * pvParameters ) {
  (void) pvParameters;

  // pox.begin() already done in setup; we call update frequently here
  for(;;) {
    pox.update(); // MUST be called as often as possible

    // If library has valid values, set shared data
    float hr = pox.getHeartRate();
    float s = pox.getSpO2();

    // Use conservative thresholds to ensure validity
    if (hr > 30.0 && s > 70.0) {
      // Acquire mutex quickly and store new pox values
      if (xSemaphoreTake(xDataMutex, (TickType_t)5) == pdTRUE) {
        latest.heartRate = hr;
        latest.spO2 = s;
        latest.timestamp = millis();
        xSemaphoreGive(xDataMutex);
      }
      // signal that there's a new pox reading (optional)
      newPoxReading = true;
    }

    // yield to scheduler but don't block long (allow other tasks to run)
    taskYIELD();
  }
}

// ---------- DS18B20 Task (Lower priority) ----------
void Task_DS18B20( void * pvParameters ) {
  (void) pvParameters;
  const TickType_t xDelay = pdMS_TO_TICKS(1000); // 1 second
  for(;;) {
    sensors.requestTemperatures(); // non-blocking for 1-wire lib (returns immediately)
    float t = sensors.getTempCByIndex(0);

    // store temp safely
    if (t != DEVICE_DISCONNECTED_C) {
      if (xSemaphoreTake(xDataMutex, (TickType_t)10) == pdTRUE) {
        latest.temperature = t;
        latest.timestamp = millis();
        xSemaphoreGive(xDataMutex);
      }
    }

    vTaskDelay(xDelay);
  }
}

// ---------- Network/Send Task (Lowest priority) ----------
void Task_Network( void * pvParameters ) {
  (void) pvParameters;

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(pdMS_TO_TICKS(200));
  }

  const TickType_t xSendDelay = pdMS_TO_TICKS(700); // send every 700 ms (adjust)
  for(;;) {
    SensorData copy;
    // copy shared data under mutex
    if (xSemaphoreTake(xDataMutex, (TickType_t)50) == pdTRUE) {
      copy = latest;
      xSemaphoreGive(xDataMutex);
    } else {
      // if couldn't take mutex, skip this cycle
      vTaskDelay(xSendDelay);
      continue;
    }

    // If we have valid data (heartRate and spO2 > thresholds), send
    if (copy.heartRate > 0 && copy.spO2 > 0 && copy.temperature != 0) {
      // Build payload (CSV) — you can change to JSON if Flask expects it
      String payload = String(copy.heartRate,1) + "," + String(copy.spO2,1) + "," + String(copy.temperature,1);

      // POST to server
      HTTPClient http;
      WiFiClient client;
      http.begin(client, serverName);
      http.addHeader("Content-Type","application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(payload);
      if (httpResponseCode > 0) {
        String res = http.getString();
        Serial.printf("[HTTP %d] %s\n", httpResponseCode, res.c_str());
      } else {
        Serial.printf("[HTTP ERROR] %d\n", httpResponseCode);
      }
      http.end();
    } else {
      // optional debug
      // Serial.println("Incomplete data, skip send");
    }

    vTaskDelay(xSendDelay);
  }
}

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("ESP32 RTOS sensor example starting...");

  // Mutex for shared sensor data
  xDataMutex = xSemaphoreCreateMutex();
  if (xDataMutex == NULL) {
    Serial.println("Failed to create mutex");
    while (1);
  }

  // Initialize I2C
  Wire.begin(); // SDA = 21, SCL = 22 by default (ESP32)
  // Initialize MAX30100
  if (!pox.begin()) {
    Serial.println("FAILED: Could not find MAX30100 sensor. Check wiring.");
    while (1);
  } else {
    Serial.println("SUCCESS: MAX30100 Found.");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
  // Optionally tune LED current if needed:
  // pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  // Initialize DS18B20
  sensors.begin();
  Serial.println("SUCCESS: DS18B20 Initialized.");

  // Connect WiFi (non-blocking connect)
  Serial.printf("Connecting to WiFi %s\n", ssid);
  WiFi.begin(ssid, password);

  // Create tasks:
  // NOTE: priority: higher number = higher priority
  // MAX30100 task should be highest so pox.update() runs as often as possible
  xTaskCreatePinnedToCore(Task_MAX30100, "MAX30100", 4096, NULL, 3, &taskMaxHandle, 1);
  xTaskCreatePinnedToCore(Task_DS18B20, "DS18B20", 3072, NULL, 2, &taskTempHandle, 1);
  xTaskCreatePinnedToCore(Task_Network, "Network", 8192, NULL, 1, &taskNetHandle, 1);

  Serial.println("Tasks created.");
}

// ---------- Loop (not used) ----------
void loop() {
  // Nothing here — all work done in tasks
  vTaskDelay(pdMS_TO_TICKS(1000));
}
