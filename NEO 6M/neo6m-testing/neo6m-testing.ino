#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  if (gpsSerial.available() > 0) 
  {
    char c = gpsSerial.read();

    // Print the character to the Serial Monitor
    Serial.print(c);

    // Check for the end of the sentence
    if (c == '\n') {
      // Start a new line for better readability
      Serial.println();
      delay(1000);
    }
  }
}
