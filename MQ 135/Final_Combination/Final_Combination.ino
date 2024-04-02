#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int analogPin = A0;
const float slope = 1.0;
const float intercept = 0.0;
const int numReadings = 99;


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.init();
  lcd.begin(16, 2); 
  lcd.print("Gas Sensor Test");

  delay(2000);
  lcd.clear();


}

void loop() 
{
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(analogPin);
  float gasConcentration = get_Concentration(sensorValue);
  int baseline = get_Average_Baseline(sensorValue);


  Serial.print("Gas Concentration: ");
  Serial.print(gasConcentration);
  Serial.println(" ppm");

  Serial.print("Analog Value: ");
  Serial.println(baseline);
  Serial.println("");

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(gasConcentration);
  lcd.print(" ppm");

  lcd.setCursor(0, 1);
  lcd.print("Analog: ");
  lcd.print(baseline);

  delay(3000); 

}

//FUNCTION FOR GETTING CONCENTRATION
float get_Concentration(int sensorReading)
{
    return slope * sensorReading + intercept;
}

//FUNCTION FOR GETTING THE BASELINE
int get_Average_Baseline(int data)
{
    int sum = 0;

    for(int i = 0; i <= numReadings; ++i)
    {
        int sensorValue = analogRead(analogPin);

        sum = sum + sensorValue;
        delay(100); 
    }
    int avgBaseline = sum / numReadings;

    return avgBaseline;
}





















