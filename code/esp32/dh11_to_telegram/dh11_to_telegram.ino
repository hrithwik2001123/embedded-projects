#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// ================= DHT Sensor =================
#define DHTPIN 4       // GPIO pin for DHT sensor
#define DHTTYPE DHT11  // DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

// ================= MQ Sensor =================
#define MQ_PIN 34   // ESP32 analog pin (use GPIO34, 35, 36, or 39)
int mqValue = 0;

// ================= WiFi Config =================
const char* ssid     = "DESKTOP-LLIVSRG 6797";       // <-- Change this
const char* password = "950]Pc08";   // <-- Change this

// ================= Server Config =================
const char* serverName = "http://192.168.1.100:5000/test";

void setup() {
  Serial.begin(115200);

  // Start DHT
  dht.begin();

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Read sensors
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    mqValue = analogRead(MQ_PIN);

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Prepare data
    String payload = String(humidity) + "," + String(temperature) + "," + String(mqValue);

    // Send to server
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "text/plain");  

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      Serial.print("Server Response Code: ");
      Serial.println(httpResponseCode);
      Serial.print("Server Response: ");
      Serial.println(http.getString());
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(5000); // wait 5 seconds before sending next reading
}
