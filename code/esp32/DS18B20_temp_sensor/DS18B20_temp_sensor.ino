#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  Serial.print("Devices found: ");
  Serial.println(sensors.getDeviceCount());

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (tempC == -127.00) {
    Serial.println("Error: DS18B20 not detected!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" *C");
  }
  delay(1000);
}
