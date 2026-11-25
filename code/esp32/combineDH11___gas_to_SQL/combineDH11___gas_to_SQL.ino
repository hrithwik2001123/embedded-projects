#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// ================= MQ Sensor =================
#define MQ_PIN 34   // Use ESP32 ADC pin (34, 35, 36, or 39)
int mqValue = 0;

// ================= DHT Sensor =================
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ================= WiFi Config =================
const char* ssid     = "DESKTOP-LLIVSRG 6797";
const char* password = "950]Pc08";

const char* serverName =  "http://192.168.29.253:5000/test";

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

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
void send_data(String A) {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverName);
      http.addHeader("Content-Type","application/x-www-form-urlencoded");
      String httpRequestData = String(A);
      int httpResponseCode = http.POST(httpRequestData);
      Serial.println(httpResponseCode);
      if(httpResponseCode > 0) {
        String res=http.getString();
        Serial.println(res);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

// ================= Main =================
void setup() {
  Serial.begin(9600);
  dht.begin();
  setup_wifi();
}

void loop() {
  // ---- MQ Sensor ----
  mqValue = digitalRead(MQ_PIN);  // Analog read for MQ sensor
  Serial.print("MQ Sensor Value: ");
  Serial.println(mqValue);

  // ---- DHT Sensor ----
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("Temperature: ");
  Serial.println(t);

  // ---- Combine Values ----
  String values =  String(h) + "," + String(t) + "," + String(mqValue);
  Serial.print("Sending: ");
  Serial.println(values);

  // ---- Send to Server ----
  send_data(values);

  delay(1000);
}
