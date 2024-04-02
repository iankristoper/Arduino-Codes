#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns and 2 rows

void setup() 
{
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Reading void setup");
  delay(2000); // Display "LCD Test" for 2 seconds
}

void loop() 
{
  lcd.print("LCD Test");
  delay(2000); // Display "LCD Test" for 2 seconds
}
