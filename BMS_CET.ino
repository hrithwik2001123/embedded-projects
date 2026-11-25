float voltage;
int bat_percentage;
int bat_percentage1;
int analogInPin  = 34;    // Analog input pin
int sensorValue;
float calibration = 0; // Check Battery voltage using multimeter & add/subtract the value
void setup()
{
  Serial.begin(9600);

}

void loop() {
  sensorValue = analogRead(analogInPin);
  voltage = (((sensorValue * 3.3) / 4095) * 3.87  + calibration); //multiply by two as voltage divider network is 100K & 100K Resistor
  if (voltage < 0.30)
  {
    voltage = 0;
  }
  bat_percentage = mapfloat(voltage, 0 , 3.7, 0, 100); //2.8V as Battery Cut off Voltage & 4.2V as Maximum Voltage

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
  Serial.print("Analog Value = ");
  Serial.println(sensorValue);
  Serial.print("Output Voltage = ");
  Serial.println(voltage);
  Serial.print("Battery Percentage = ");
  Serial.println(bat_percentage1);
 Serial.println(bat_percentage);

 
  delay(300);

  if (bat_percentage <= 30)
  {
    Serial.println("Battery level below 30%, Charge battery on time");
    //send notification
  }

}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
