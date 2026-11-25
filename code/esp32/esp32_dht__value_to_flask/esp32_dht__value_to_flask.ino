#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

const char* ssid     = "DESKTOP-LLIVSRG 6797";
const char* password = "950]Pc08";

const char* serverName =  "http://192.168.29.253:5000/test";

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
int count=0;
void setup_wifi()
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ");
  Serial.println(ssid);
  
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) 
  { 
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
  dht.begin();
  setup_wifi();
}

void loop()
{
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  Serial.print(F("Humidity:"));
  Serial.println(h);
  Serial.print(F("Temperature:"));
  Serial.println(t);
  delay(1000);
  String values=String(h)+","+String(t);
  Serial.println(values);
  send_data(values);
}
