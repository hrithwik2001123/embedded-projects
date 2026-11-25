
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "DESKTOP-LLIVSRG 6797";
const char* password = "950]Pc08";

const char* serverName =  "http://192.168.29.253:5000/test";

unsigned long lastTime = 0;
unsigned long timerDelay = 200;
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

// ESP32 Code using RX0/TX0 pins
void setup() {
  // Serial for debugging (via USB)
  Serial.begin(9600);
   setup_wifi();
  // Serial0 (RX0/TX0) for communication with Arduino
  // Note: RX0=GPIO3, TX0=GPIO1 - These are the default pins
  Serial.begin(9600); // This uses RX0/TX0 by default
  
  // If you need both USB debugging and Arduino communication, use:
  Serial.begin(9600);  // For USB debugging
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // Use Serial2 instead (recommended)
  
  Serial.println("ESP32 Ready - Waiting for Arduino data on Serial0...");
  Serial.println("Format: HeartRate,SpO2,Temperature");
  Serial.println("===================================");
}

void loop() {
  // Check if data available from Arduino
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim();
    
    Serial.print("Raw data received: ");
    Serial.println(data);
    
    // Parse CSV data: HeartRate,SpO2,Temperature
    int firstComma = data.indexOf(',');
    int secondComma = data.indexOf(',', firstComma + 1);
    
    if (firstComma != -1 && secondComma != -1) {
      String hrStr = data.substring(0, firstComma);
      String spO2Str = data.substring(firstComma + 1, secondComma);
      String tempStr = data.substring(secondComma + 1);
      
      float heartRate = hrStr.toFloat();
      float spO2 = spO2Str.toFloat();
      float temperature = tempStr.toFloat();
      
      // Display received data
      Serial.println("✅ Data Parsed Successfully:");
      Serial.print("Heart Rate: ");
      Serial.print(heartRate);
      Serial.println(" bpm");
      
      Serial.print("SpO2: ");
      Serial.print(spO2);
      Serial.println(" %");
      
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");
      Serial.println("-------------------");
       // ---- Combine Values ----
  String values =  String(heartRate) + "," + String(spO2) + "," + String(temperature);
  Serial.print("Sending: ");
  Serial.println(values);

  // ---- Send to Server ----
  send_data(values);

    } else {
      Serial.println("❌ Error: Invalid data format");
    }
  }
  
  delay(100);
}
