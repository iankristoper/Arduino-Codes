#include <SoftwareSerial.h>

// Define the ESP-01 serial pins
#define ESP_TX 2   // Arduino RX (ESP TX)
#define ESP_RX 3   // Arduino TX (ESP RX)

// Define your Wi-Fi network credentials
const char* ssid = "...";
const char* password = "@ian/tagano???";

// Define your server details
const char* serverAddress = "192.168.254.177"; // Replace with your server's IP address
const int serverPort = 80;

// Create a software serial port for ESP-01 communication
SoftwareSerial espSerial(ESP_RX, ESP_TX);

void setup() 
{
  Serial.begin(115200);
  espSerial.begin(115200); // Start ESP-01 serial communication
  connectToWiFi();
}

void loop() 
{
  if (espSerial.available()) 
  {
    Serial.write(espSerial.read()); // Pass data from ESP-01 to Arduino Serial monitor
  }

  // Send data to the server through ESP-01
  sendDataToServer("Hello, Server!");
  delay(5000);
}

void connectToWiFi() 
{
  Serial.println("Connecting to WiFi");
  espSerial.println("AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"");
  delay(10000); // Wait for Wi-Fi connection
  if (espSerial.find("OK")) 
  {
    Serial.println("WiFi connected");
  } 
  else 
  {
    Serial.println("WiFi connection failed");
  }
}

void sendDataToServer(String data) 
{
  espSerial.println("AT+CIPSTART=\"TCP\",\"" + String(serverAddress) + "\"," + String(serverPort));
  delay(10000); // Wait for connection to establish
  if (espSerial.find("CONNECT")) 
  {
    Serial.println("Connected to server");
    espSerial.println("AT+CIPSEND=" + String(data.length() + 4)); // +4 for additional overhead
    delay(2000); // Wait for prompt

    if (espSerial.find(">")) 
    {
      espSerial.println(data);
      delay(2000); // Wait for data to be sent

      if (espSerial.find("SEND OK")) 
      {
        Serial.println("Data sent to server");
      } 
      else 
      {
        Serial.println("Failed to send data to server");
      }
    } 
    else 
    {
      Serial.println("Failed to establish data sending");
    }
  } 
  else 
  {
    Serial.println("Failed to connect to server");
  }
  delay(5000); // Wait before sending next data
}


