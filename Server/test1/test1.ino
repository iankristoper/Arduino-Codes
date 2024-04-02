#include <WiFi.h>

// WiFi credentials
const char* ssid = "...";
const char* password = "@ian/tagano???";

// Server details
const char* serverAddress = "192.168.1.100"; // Replace with your laptop's IP address
const int serverPort = 80;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  connectToWiFi();
}

void loop() {
  if (!client.connected()) {
    if (client.connect(serverAddress, serverPort)) {
      Serial.println("Connected to server");
      client.println("GET / HTTP/1.1");
      client.println("Host: " + String(serverAddress));
      client.println("Connection: close");
      client.println();
    } else {
      Serial.println("Connection to server failed");
    }
  }

  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server");
    client.stop();
    delay(5000); // Wait before attempting to reconnect
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
