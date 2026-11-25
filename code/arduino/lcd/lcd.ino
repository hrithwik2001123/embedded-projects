#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4, 5, 6, 7);

void setup()
 {
  lcd.begin(16, 2);            // Initialize 16x2 LCD
  lcd.print("Hello, World!");  // Print on first line
}

void loop()
 {
  lcd.clear(); 
  lcd.setCursor(0, 1);         // Move cursor to column 0, row 1 (second line)
  lcd.print("Arduino LCD!");   // Print on second line
  delay(2000);                 // Wait 2 seconds
  lcd.clear();                 // Clear the display
  lcd.setCursor(0, 0);
  lcd.print("Hello Again!");
  
  delay(2000);
}
