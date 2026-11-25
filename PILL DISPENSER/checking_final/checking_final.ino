#include <OneWire.h>
#include <ESP32Servo.h>
#include <DFRobotDFPlayerMini.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Servo myservo;
Servo myservo1;
Servo myservo2;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C
#define SDA_PIN 21
#define SCL_PIN 22
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "redmi13C";
const char* password = "aswaniis";
const char* serverName ="http://10.38.31.241:5000/test";
const char* serverName1 ="http://10.38.31.241:5000/check";
const char* serverName2 ="http://10.38.31.241:5000/box_checking";
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
unsigned long lastTime1 = 0;
unsigned long timerDelay1 = 1000;
int pix=15;
float trig = 18;
float echo = 5;

int buz = 4;
int i = 0;
int c=0;
int led1=27;
int led2=26;
int led3=25;
float duration;
long distance;
HardwareSerial mySerial(2);
DFRobotDFPlayerMini myDFPlayer;
bool flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
bool ir1flag = 0, ir2flag = 0, ir3flag = 0;
bool ir1flag1=0,ir2flag2=0,ir3flag3=0,ir1flag4=0,ir2flag5=0,ir3flag6=0;
bool check_flag=0,send_flag=0;
int s1cnt = 0, s2cnt = 0, s3cnt = 0;
String mname="";
void setup_wifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("CONNECTING.....");
  }
  Serial.println("CONNECTED");
}

void sendData(String val1) {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = String(val1);
      int httpResponseCode = http.POST(httpRequestData);
      Serial.println(httpResponseCode);

      if (httpResponseCode > 0) {
        String res = http.getString();
        Serial.println(res);
        if (res == "1") 
        {
          res="ok";
          flag1 = 1;
        } else if (res == "2") 
        {
          res="ok";
          flag2 = 1;
        } else if (res == "3") 
        {
          res="ok";
          flag3 = 1;
        }
        
        else if (res == "ok") 
        {

        }
        else
        {
          
          displayMedicine(res);
          Serial.println("Helloooo");
         }
      }
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}


void initMP3()
{
  mySerial.begin(9600, SERIAL_8N1, 33, 32); // RX, TX
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Error");
    return;
  }
  myDFPlayer.volume(25); // 0–30
  Serial.println("DFPlayer Ready");
}

void playMedicine1()
{
  myDFPlayer.play(1); // file 0001.mp3
}

void playMedicine2()
{
  myDFPlayer.play(2);
}

void playMedicine3()
{
  myDFPlayer.play(3);
}

void emergency(String val) {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverName1);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = String(val);
      int httpResponseCode = http.POST(httpRequestData);
      Serial.println(httpResponseCode);

      if (httpResponseCode > 0) {
        String res = http.getString();
        Serial.println(res);
      }
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
///////////////////////////////////////////////////



void displayMedicine(String message)
{
  if(pix==15)
  {
  display.clearDisplay();
  }
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(1,pix);
  display.print(message);
  display.display();
  pix=pix+15;
  if(pix>45)
  {
    pix=15;
  }
  delay(1000);
}
void displayMessage(String message)
{
  pix=15;
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(1,15);
  display.print(message);
  display.display();
  delay(1000);
}


void setup() 
{
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
  displayMessage("WELCOME");
  initMP3();
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  myservo.setPeriodHertz(50);
  myservo1.setPeriodHertz(50);
  myservo2.setPeriodHertz(50);
  myservo.attach(13,500,2400);
  myservo1.attach(14,500,2400);
  myservo2.attach(12,500,2400);
  myservo.write(150);
  myservo1.write(150);
  myservo2.write(150);
  setup_wifi();
  digitalWrite(buz, HIGH);
  delay(500);
  digitalWrite(buz, LOW);
  delay(500);
}

void loop() 
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  distance = duration*0.034/2;
  Serial.println(distance);
  if(check_flag==0)
  {
    sendData("data");
  }
  if(flag1==1)
  {
    flag1=0;
    playMedicine1();
    Serial.print("starts mp3-1");
    digitalWrite(buz, HIGH);
    digitalWrite(led1, HIGH);
   myservo.write(150);
   delay(500);
   myservo.write(60);
    delay(500);
    sendData("data");
    digitalWrite(buz, LOW);
    check_flag=1;
    delay(1000);
  }
 if(flag2==1)
  {
    flag2=0;
    playMedicine2();
    Serial.print("starts mp3-2");
    digitalWrite(buz, HIGH);
    digitalWrite(led2, HIGH);
    delay(1000);
 myservo1.write(150);
 delay(500);
 myservo1.write(60);
  delay(500);
    sendData("data");
    digitalWrite(buz, LOW);
     check_flag=1;
    delay(1000);
  }
  if(flag3==1)
  {
    flag3=0;
    playMedicine3();
    Serial.print("starts mp3-3");
     digitalWrite(buz, HIGH);
     digitalWrite(led3, HIGH);
    delay(1000);
 myservo2.write(150);
 delay(500);
 myservo2.write(60);
  delay(500);
    sendData("data");
    digitalWrite(buz, LOW);
     check_flag=1;
    delay(1000);
  }
     if(check_flag==1)
  {
    sendData("data");
    c++;
    if(distance <=10)
    {
      c=0;
      check_flag=0;
      digitalWrite(buz, HIGH);
      delay(1000);
      digitalWrite(buz, LOW);
      delay(1000);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      displayMessage("pill taken");
    }
    if(c>3000)
    {
      c=0;
      check_flag=0;
      delay(2000);
      displayMessage("NOT TOOK MEDICINE");
      emergency("X");
      delay(2000);
      displayMessage("WELCOME");
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      displayMessage("WELCOME");
    }
  }
  

}
