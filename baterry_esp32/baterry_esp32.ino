#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "Arjun_pointbreak";
const char* password = "1234@1234";
const char* serverName = "http://10.196.130.72:5000/battery";

float voltage;
int bat_percentage;
int bat_percentage1;
int analogInPin  = 34;
int sensorValue;
float calibration = 0;

void setup()
{
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {

  sensorValue = analogRead(analogInPin);
  voltage = (((sensorValue * 3.3) / 4095) * 3.87 + calibration);

  if (voltage < 0.30)
  {
    voltage = 0;
  }

  bat_percentage = mapfloat(voltage, 0 , 3.7, 0, 100);

  
  if (voltage < 7.0)
  {
    bat_percentage1 = 0;
  }
  else if (voltage < 8.0)
  {
    bat_percentage1 = 0;
  }
  else if (voltage < 9.0)
  {
    bat_percentage1 = 20;
  }
  else if (voltage < 10.0)
  {
    bat_percentage1 = 40;
  }
  else if (voltage < 11.0)
  {
    bat_percentage1 = 60;
  }
  else if (voltage < 12.0)
  {
    bat_percentage1 = 80;
  }
  else
  {
    bat_percentage1 = 100;
  }

  Serial.print("Battery Percentage = ");
  Serial.println(bat_percentage1);

  // 🔹 Send to Flask
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"battery\":" + String(bat_percentage1) + "}";

    int httpResponseCode = http.POST(jsonData);

    Serial.print("HTTP Response: ");
    Serial.println(httpResponseCode);

    http.end();
  }

  delay(3000);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}