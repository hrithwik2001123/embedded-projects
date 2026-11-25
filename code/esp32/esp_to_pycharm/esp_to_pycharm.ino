#include <WiFi.h>         // ESP32 WiFi
#include <HTTPClient.h>   // HTTP functions


const char* ssid     = "red";
const char* password = "redmi123";

const char* serverName =  "http://192.168.183.172:5000/test";


unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
int count=0;
void setup_wifi()
{
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) 
  { 
    delay(500);
    Serial.println("CONNECTING.....");
  }
  Serial.println("CONNECTED");
}

void send_data(String A)
{
  if ((millis() - lastTime) > timerDelay)
  {
    if(WiFi.status()== WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverName);
      http.addHeader("Content-Type","application/x-www-form-urlencoded");
      String httpRequestData=String(A);
      int httpResponseCode=http.POST(httpRequestData);
      Serial.println(httpResponseCode);
      if(httpResponseCode>0)
      {
        String res=http.getString();
        Serial.println(res);
      }
      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void setup()
{
  Serial.begin(9600);
  setup_wifi();
}

void loop()
{
    send_data("Hai");
}
