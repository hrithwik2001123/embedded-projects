#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// ================= WiFi Config =================

const char* ssid     = "DESKTOP-LLIVSRG 6797";
const char* password = "950]Pc08";

// Flask Server (PC running Flask)
const char* serverName = "http://192.168.29.253:5000/gps";  
// 🔹 Replace 192.168.1.100 with your PC’s IP address

// ================= GPS Setup =================
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);  // use UART1 for GPS (TX=GPIO17, RX=GPIO16)

// ================= Setup =================
void setup() {
  Serial.begin(115200);       // Debugging
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);  // GPS module RX=16, TX=17

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to WiFi!");
}

// ================= Loop =================
void loop() {
  // Read GPS data
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }

  if (gps.location.isUpdated()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();

    Serial.print("Latitude: "); Serial.println(latitude, 6);
    Serial.print("Longitude: "); Serial.println(longitude, 6);

    // Send to Flask server
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "text/plain");

      String postData = String(latitude, 6) + "," + String(longitude, 6);
      int httpResponseCode = http.POST(postData);

      if (httpResponseCode > 0) {
        Serial.println("✅ Data sent: " + postData);
        Serial.println("Response: " + http.getString());
      } else {
        Serial.println("❌ Error sending data");
      }
      http.end();
    } else {
      Serial.println("⚠ WiFi Disconnected!");
    }

    delay(5000);  // Send every 5 seconds
  }
}
