#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Adafruit_MPU6050 mpu;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  
  Serial.println("Initializing MPU6050...");

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip!");
    lcd.clear();
    lcd.print("MPU6050 Not");
    lcd.setCursor(0, 1);
    lcd.print("Found!");
    while (1) delay(10);
  }
  
  Serial.println("MPU6050 Found!");
  lcd.clear();
  lcd.print("MPU6050 Found!");

  // Set accelerometer range
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  
  // Set gyroscope range
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  
  // Set filter bandwidth
  mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);

  delay(2000);
  lcd.clear();
  Serial.println("Setup complete.\n");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Display accelerometer data on LCD
  lcd.setCursor(0, 0);
  lcd.print("AX:");
  lcd.print(a.acceleration.x, 1);
  lcd.print(" ");
  lcd.print("AY:");
  lcd.print(a.acceleration.y, 1);

  lcd.setCursor(0, 1);
  lcd.print("AZ:");
  lcd.print(a.acceleration.z, 1);
  lcd.print(" ");
  lcd.print("T:");
  lcd.print(temp.temperature, 1);

  // Print to Serial for debugging
  Serial.print("AX: "); Serial.print(a.acceleration.x, 2);
  Serial.print(" AY: "); Serial.print(a.acceleration.y, 2);
  Serial.print(" AZ: "); Serial.print(a.acceleration.z, 2);
  Serial.print(" m/s^2");
  
  Serial.print(" | GX: "); Serial.print(g.gyro.x, 2);
  Serial.print(" GY: "); Serial.print(g.gyro.y, 2);
  Serial.print(" GZ: "); Serial.print(g.gyro.z, 2);
  Serial.print(" rad/s");
  
  Serial.print(" | Temp: "); Serial.print(temp.temperature, 1);
  Serial.println(" °C");

  delay(200);  // Update every 200ms for better LCD readability
}
