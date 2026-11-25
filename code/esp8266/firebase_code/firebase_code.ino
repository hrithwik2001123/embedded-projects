#include <ESP8266WiFi.h>
#include <FirebaseEsp8266.h>  // Use this header if library installs with this name
#include <SoftwareSerial.h>

#define WIFI_SSID "F.R.I.D.I"
#define WIFI_PASSWORD "12348765"
#define FIREBASE_HOST "renjit9645-af2fe-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "shdIcL6IJPalf8KnUVCK5M9KfBgJdMWWpc3m60vU"

SoftwareSerial uno(D6, D7);  // RX, TX
FirebaseData firebaseData;
int Power = 0;

void setup() {
  Serial.begin(9600);
  uno.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.getString(firebaseData, "/L1")) {
    Power = firebaseData.stringData().toInt();
    Serial.println("Power: " + String(Power));
    uno.write(Power);
  } else {
    Serial.println("Firebase read failed: " + firebaseData.errorReason());
  }

  delay(500);
}
