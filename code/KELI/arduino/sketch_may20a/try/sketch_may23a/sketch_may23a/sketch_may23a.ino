const int sensorPin = A0;       // ZMPT101B analog output connected to A0
const float VREF = 5.0;         // ADC reference voltage (5V on Nano)
const int ADC_RES = 1024;       // 10-bit ADC
float calibration = 250.0;      // Calibration factor (adjust based on test)

void setup() {
  Serial.begin(9600);
}

void loop() {
  float voltage = getACVoltage();
  Serial.print("AC Voltage (RMS): ");
  Serial.print(voltage);
  Serial.println(" V");
  delay(1000);
}

float getACVoltage() {
  const int samples = 1000;
  float sumSquares = 0.0;

  for (int i = 0; i < samples; i++) {
    int raw = analogRead(sensorPin);
    float voltageCentered = ((float)raw - 512.0) * (VREF / ADC_RES);
    sumSquares += voltageCentered * voltageCentered;
  }

  float rms = sqrt(sumSquares / samples);
  return rms * calibration;
}
