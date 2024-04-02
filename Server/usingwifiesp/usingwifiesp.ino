#include "WiFiEsp.h"
#include <SoftwareSerial.h>

// Define your Wi-Fi network credentials
const char* ssid = "...";         // Replace with your Wi-Fi network SSID
const char* password = "@ian/tagano???";        // Replace with your Wi-Fi network password


// Define your server details
const char* serverAddress = "192.168.254.177";  // Replace with your server's IP address
const int serverPort = 80;                      // Assuming your server is running on port 80


// Define software serial pins
#define RX_PIN 2   // Arduino digital pin 2 is used as RX
#define TX_PIN 3   // Arduino digital pin 3 is used as TX

SoftwareSerial espSerial(RX_PIN, TX_PIN);  // Create a SoftwareSerial object
WiFiEspClient client;   // Create a client object to communicate with the server



void setup() 
{
  
  Serial.begin(9600);     // Initialize serial communication for debugging
  espSerial.begin(9600);    // Initialize SoftwareSerial communication with ESP module

  // Initialize ESP module
  WiFi.init(&espSerial);

  // Connect to Wi-Fi
  connectToWiFi();
}

void loop() 
{
  // Send data to the server
  sendDataToServer("Ian Christopher Cutie nananana");
  delay(10000); // Wait for 10 seconds before sending next data
}





void connectToWiFi() 
{
  Serial.println("Connecting to WiFi");

  // Attempt to connect to Wi-Fi network
  int status = WiFi.begin(ssid, password);
  int attempts = 0;

  if (status == WL_CONNECTED) 
  {
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else 
  {
    Serial.println("Failed to connect to WiFi");
  }
}



void sendDataToServer(String data) 
{
  // Check if client is connected to the server
  if (client.connect(serverAddress, serverPort)) 
  {
    Serial.println("Connected to server."); 
    
    // Construct the HTTP POST request
    String postRequest = "POST /Arduino_server/receive_data.php HTTP/1.1\r\n";
    postRequest += "Host: " + String(serverAddress) + "\r\n";
    postRequest += "Content-Type: application/x-www-form-urlencoded\r\n";
    postRequest += "Content-Length: " + String(data.length() + 5) + "\r\n"; // Include "data=" prefix length
    postRequest += "Connection: close\r\n\r\n";
    postRequest += "data=" + data;
    
    // Send the POST request
    client.println(postRequest);
    Serial.println("Request sent");
    Serial.println(data);

    // Wait for the server response
    delay(2000);

    // Read and print the server response
    while (client.available()) 
    {
      char c = client.read();
      Serial.print(c);
    }

    delay(2000);
    // Close the connection
    client.stop();
  } 
  else 
  {
    Serial.println("Connection to server failed");
  }
}




/*
void sendDataToServer(String data) 
{
  // Check if client is connected to the server
  if (client.connect(serverAddress, serverPort)) 
  {
    Serial.println("Connected to server."); 
    
    // Construct the HTTP POST request
    String postRequest = "POST /Arduino_server/receive_data.php HTTP/1.1\r\n";
    postRequest += "Host: " + String(serverAddress) + "\r\n";
    postRequest += "Content-Type: application/x-www-form-urlencoded\r\n";
    postRequest += "Content-Length: " + String(data.length()) + "\r\n";
    postRequest += "Connection: close\r\n\r\n";
    postRequest += "data=" + data;
    
    // Send the POST request
    client.println(postRequest);
    Serial.println("Request sent");
    Serial.println(data);

    // Wait for the server response
    delay(2000);

    // Read and print the server response
    while (client.available()) 
    {
      char c = client.read();
      Serial.print(c);
    }

    delay(2000);
    // Close the connection
    client.stop();
  } 
  else 
  {
    Serial.println("Connection to server failed");
  }
}
*/
















