#include <Wire.h> // For I2C communication
#include "MAX30100_PulseOximeter.h" // For the MAX30100 library

// Define how often to report sensor readings
#define REPORTING_PERIOD_MS 1000

// Create a PulseOximeter object
PulseOximeter pox;
uint32_t tsLastReport = 0;

// Callback function fired when a pulse is detected
void onBeatDetected() {
  Serial.println("Beat!");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing MAX30100...");

  // Initialize the PulseOximeter instance
  if (!pox.begin()) {
    Serial.println("FAILED: Could not find MAX30100 sensor. Check wiring.");
    for (;;);
  } else {
    Serial.println("SUCCESS: Sensor found.");
  }

  // Register the beat detection callback
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  // Update the sensor readings as fast as possible
  pox.update();

  // Print readings once per second
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    float heartRate = pox.getHeartRate();
    float spo2 = pox.getSpO2();

    // Check if the sensor returns a valid reading (not 0)
    if (heartRate > 0 && spo2 > 0) {
      Serial.print("Heart rate: ");
      Serial.print(heartRate);
      Serial.print(" bpm / SpO2: ");
      Serial.print(spo2);
      Serial.println("%");
    } else {
      Serial.println("Waiting for valid readings... Place finger firmly on sensor.");
    }
    
    tsLastReport = millis();
  }
}
