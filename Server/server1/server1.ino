#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFi.h>

// WiFi credentials
const char* ssid = "...";
const char* password = "@ian/tagano???";

// Server details
const char* serverAddress = "192.168.254.177"; // Replace with your laptop's IP address
const int serverPort = 80;

// Choose two Arduino pins to use for software serial
int RXPin = 2;
int TXPin = 3;
int GPSBaud = 115200;

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

// Create a WiFiClient object to connect to the server
WiFiClient client;

void setup() {
  // Start the Arduino hardware serial port at 9600 baud for debugging
  Serial.begin(115200);

  // Start the software serial port at the GPS's baud rate
  gpsSerial.begin(GPSBaud);

  // Connect to WiFi
  connectToWiFi();
}

void loop() {
  // Update GPS data
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      sendGPSDataToServer();
    }
  }
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void sendGPSDataToServer() {
  if (client.connect(serverAddress, serverPort)) {
    Serial.println("Connected to server");
    
    // Construct HTTP request with GPS coordinates
    String url = "/receive_gps.php?lat=" + String(gps.location.lat(), 6) + "&lon=" + String(gps.location.lng(), 6);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + serverAddress + "\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.println("GPS data sent");
  } else {
    Serial.println("Connection to server failed");
  }
}
