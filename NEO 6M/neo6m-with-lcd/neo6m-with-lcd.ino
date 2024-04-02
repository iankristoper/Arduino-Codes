#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

int RXPin = 2;
int TXPin = 3;
int GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns and 2 rows

void setup() 
{
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Reading...");
  delay(2000);
  lcd.clear();
}

void loop() 
{
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10) 
  {
    Serial.println("No GPS detected");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No GPS detected");
    while (true);
  }
}

void displayInfo() 
{
  if (gps.location.isValid()) 
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 15);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 15);

    displayScrolling("Lat: ", String(gps.location.lat(), 15), 0);
    displayScrolling("Lon: ", String(gps.location.lng(), 15), 1);
    delay(5000); // Wait for 5 seconds
  } 
  else 
  {
    Serial.println("Location: N/A");
    lcd.setCursor(0, 0);
    lcd.print("Location: N/A");
  }
}

void displayScrolling(String prefix, String value, int row) 
{
  int length = prefix.length() + value.length();
  for (int i = 0; i <= length - 16; i++) 
  {
    lcd.setCursor(0, row);
    lcd.print(prefix);
    lcd.print(value.substring(i, i + 16));
    delay(5000); // Adjust delay to control scrolling speed
  }
}

/*
  if (gps.location.isValid())
  {
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    lcd.setCursor(0, 1);
    lcd.print("Lon: ");
    lcd.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.println("Location: N/A");
    lcd.setCursor(0, 1);
    lcd.print("Location: N/A");
  }
*/
/*
  if (gps.time.isValid())
  {
    Serial.print("Time: ");
    Serial.print(gps.time.hour());
    Serial.print(":");
    Serial.print(gps.time.minute());
    Serial.print(":");
    Serial.println(gps.time.second());
    lcd.setCursor(10, 0);
    lcd.print("Time: ");
    lcd.print(gps.time.hour());
    lcd.print(":");
    lcd.print(gps.time.minute());
    lcd.print(":");
    lcd.print(gps.time.second());
  }
  else
  {
    Serial.println("Time: N/A");
    lcd.setCursor(10, 0);
    lcd.print("Time: N/A");
  }
*/

