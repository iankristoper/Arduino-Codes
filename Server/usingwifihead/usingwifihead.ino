#include <WiFi.h>
#include <SoftwareSerial.h>

// Define your Wi-Fi network credentials
const char* ssid = "...";
const char* password = "@ian/tagano???";

// Define your server details
const char* serverAddress = "192.168.254.177"; // Replace with your server's IP address
const int serverPort = 80;

// Create a software serial port for ESP-01 communication
#define ESP_RX 2   // Arduino RX (ESP TX)
#define ESP_TX 3   // Arduino TX (ESP RX)
SoftwareSerial espSerial(ESP_RX, ESP_TX);

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200); // Start ESP-01 serial communication
  connectToWiFi();
}

void loop() {
  if (espSerial.available()) {
    Serial.write(espSerial.read()); // Pass data from ESP-01 to Arduino Serial monitor
  }

  // Send data to the server through ESP-01
  sendDataToServer("h");
  delay(10000); // Wait for 5 seconds before sending next data
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void sendDataToServer(String data) {
  // Construct the full URL with the data parameter
  String url = "http://192.168.254.177/arduino_server/receive_data.php/test=" + data;

  // Establish TCP connection with the server
  WiFiClient client;
  if (client.connect(serverAddress, serverPort)) {
    Serial.println("Connected to server");

    // Make HTTP GET request
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + serverAddress + "\r\n" +
                 "Connection: close\r\n\r\n");
    delay(1000); // Wait for data to be sent

    // Check HTTP response
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    client.stop();
    Serial.println("Data sent to server");
  } else {
    Serial.println("Failed to connect to server");
  }
}
