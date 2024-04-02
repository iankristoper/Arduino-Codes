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

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200); // Start ESP-01 serial communication
  connectToWiFi();
}

void loop() {
  // Send data to the server through ESP-01
  sendDataToServer("Hello from Arduino");
  delay(10000); // Wait for 10 seconds before sending next data
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi");
  espSerial.println("AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"");
  delay(5000); // Wait for Wi-Fi connection
  if (espSerial.find("OK")) {
    Serial.println("WiFi connected");
  } else {
    Serial.println("WiFi connection failed");
  }
}

void sendDataToServer(String data) {
  // Construct the full URL
  String url = "/arduino_server/ping.php";

  // Calculate the content length
  int contentLength = data.length();

  // Send HTTP POST request to the server
  espSerial.println("AT+CIPSTART=\"TCP\",\"" + String(serverAddress) + "\"," + String(serverPort));
  delay(2000); // Wait for connection to establish

  if (espSerial.find("CONNECT")) {
    Serial.println("Connected to server");

    // Send the length of the URL and data
    espSerial.print("AT+CIPSEND=");
    espSerial.println(url.length() + 2 + contentLength + 38); // 38 additional characters for POST data format
    delay(1000); // Wait for prompt

    if (espSerial.find(">")) {
      // Send the POST request header
      espSerial.println("POST " + url + " HTTP/1.1");
      espSerial.println("Host: " + String(serverAddress));
      espSerial.println("Content-Type: application/x-www-form-urlencoded");
      espSerial.print("Content-Length: ");
      espSerial.println(contentLength);
      espSerial.println();
      // Send the POST data
      espSerial.println("data=" + data);
      delay(1000); // Wait for data to be sent

      // Check if data sent successfully
      if (espSerial.find("SEND OK")) {
        Serial.println("Data sent to server");
      } else {
        Serial.println("Failed to send data to server");
      }
    } else {
      Serial.println("Failed to establish data sending");
    }
  } else {
    Serial.println("Failed to connect to server");
  }
}




