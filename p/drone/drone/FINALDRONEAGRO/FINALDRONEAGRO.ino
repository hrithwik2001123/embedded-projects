#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>

// ================= WIFI =================
const char* ssid = "ABCDE";
const char* password = "12345678";

// ================= TELEGRAM =================
#define BOT_TOKEN "8606874507:AAFVFZ_2Ms55_F9hS8Cnr9bbH6ut6tFcsXg"
#define CHAT_ID "8581792634"

// ================= PINS =================
#define RELAY_PIN D1      // GPIO5 (ACTIVE LOW)
#define DHT_PIN   D2      // GPIO4
#define DHT_TYPE  DHT11

// ================= OBJECTS =================
ESP8266WebServer server(80);
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
DHT dht(DHT_PIN, DHT_TYPE);

// ================= VARIABLES =================
bool relayState = false;
unsigned long lastTelegramCheck = 0;

// ================= RELAY PULSE (2 sec) =================
void handleRelayPulse() {

  // 🔴 RELAY ON (ACTIVE LOW)
  digitalWrite(RELAY_PIN, HIGH);
  relayState = true;

  bot.sendMessage(CHAT_ID,
    "⚠️ Leaf disease detected!\n🚿 Relay ON for 2 seconds", "");

  delay(2000);

  // 🟢 RELAY OFF
  digitalWrite(RELAY_PIN, LOW);
  relayState = false;

  bot.sendMessage(CHAT_ID, "✅ Relay OFF automatically", "");
  server.send(200, "text/plain", "Relay ON for 2 seconds");
}

// ================= TELEGRAM COMMAND =================
void checkTelegram() {
  int newMsg = bot.getUpdates(bot.last_message_received + 1);

  while (newMsg) {
    for (int i = 0; i < newMsg; i++) {

      String chat_id = bot.messages[i].chat_id;
      String text = bot.messages[i].text;

      if (chat_id != CHAT_ID) continue;

      // ===== /TEMP COMMAND =====
      if (text == "/TEMP") {
        float h = dht.readHumidity();
        float t = dht.readTemperature();

        String msg = "🌱 ESP8266 STATUS\n";

       
          msg += "🌡 Temperature: " + String(t) + " °C\n";
          msg += "💧 Humidity: " + String(h) + " %\n";
    

        msg += "🔌 Relay Status: ";
        msg += relayState ? "ON" : "OFF";

        bot.sendMessage(chat_id, msg, "");
      }
    }
    newMsg = bot.getUpdates(bot.last_message_received + 1);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);   // Relay OFF
  relayState = false;

  dht.begin();
  client.setInsecure();

  // ================= WIFI =================
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());
  IPAddress ip = WiFi.localIP();
  Serial.print("ESP IP Address: ");
  Serial.println(ip);

  // ---------- SEND IP TO TELEGRAM ----------
  String message = "📡 *ESP8266 Connected*\n";
  message += "🛜 WiFi: " + String(ssid) + "\n";
  message += "🌐 IP Address: " + ip.toString();

  bot.sendMessage(CHAT_ID, message, "Markdown");
  bot.sendMessage(
    CHAT_ID,
    "📡 ESP8266 Online\nSend /TEMP to get DHT + Relay status",
    ""
  );

  // ================= HTTP =================
  server.on("/relay/pulse", handleRelayPulse);
  server.begin();
}

void loop() {
  server.handleClient();

  // Check Telegram every 2 seconds
  if (millis() - lastTelegramCheck > 2000) {
    checkTelegram();
    lastTelegramCheck = millis();
  }
}
