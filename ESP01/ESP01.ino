#include <SoftwareSerial.h>

// Define the RX and TX pins for ESP-01 module
const int espRX = 0; // Connect ESP-01 TX to Arduino pin 2
const int espTX = 1; // Connect ESP-01 RX to Arduino pin 3

// Create a SoftwareSerial object for ESP-01 communication
SoftwareSerial espSerial(espRX, espTX);

void setup() 
{
  // Initialize serial communication for debugging
  Serial.begin(115200);
  
  // Initialize serial communication with ESP-01 module
  espSerial.begin(115200);

  // Wait for ESP-01 module to initialize
  delay(1000);
  
  // Send AT command to ESP-01 module
  espSerial.println("AT");
}

void loop() {
  // Check if data is available from ESP-01 module
  if (espSerial.available()) {
    // Read data from ESP-01 module
    char receivedChar = espSerial.read();
    
    // Print received data to serial monitor
    Serial.print(receivedChar);
  }
  
  // Check if data is available from serial monitor (for sending commands)
  if (Serial.available()) {
    // Read data from serial monitor
    char commandChar = Serial.read();
    
    // Send command to ESP-01 module
    espSerial.write(commandChar);
  }
}
