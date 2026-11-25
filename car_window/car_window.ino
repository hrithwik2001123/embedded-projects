#define BLYNK_TEMPLATE_ID "TMPL3ZepHMDkL"
#define BLYNK_TEMPLATE_NAME "car window"
#define BLYNK_AUTH_TOKEN "zQQYW39LUv8bWRdj2L3Bem00ZDdnaqXC"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "IQ0oz9";
char pass[] = "12345678";

#define IN1 12
#define IN2 14
#define BUZ 23
#define MQ_PIN 34


int forwardState = 0;
int backwardState = 0;

void motorForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void motorBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motorStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void controlMotor() {
  if (forwardState == 1 && backwardState == 0) {
    motorForward();
  }
  else if (backwardState == 1 && forwardState == 0) {
    motorBackward();
  }
  else {
    motorStop();
  }
}

BLYNK_WRITE(V0) {
  forwardState = param.asInt();
  controlMotor();
}

BLYNK_WRITE(V1) {
  backwardState = param.asInt();
  controlMotor();
}

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(BUZ, OUTPUT);

  motorStop();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int mqValue = analogRead(MQ_PIN);
  int mqPercent = map(mqValue, 0, 4095, 0, 100);

  Serial.print("Raw: ");
  Serial.print(mqValue);
  Serial.print("  %: ");
  Serial.println(mqPercent);

  Blynk.virtualWrite(V3, mqPercent);
  if (mqPercent >= 40) {
    digitalWrite(BUZ, HIGH);
    motorBackward();
    delay(700);
    motorStop();
  }
  else
  {
    digitalWrite(BUZ, LOW);
  }

  delay(1000);
}
