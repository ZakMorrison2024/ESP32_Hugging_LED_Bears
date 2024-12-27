#include <WiFi.h>
#include <WiFiUdp.h>

#define WIFI_SSID "YourSSID"
#define WIFI_PASS "YourPassword"
#define TEMP_PIN 4      // Pin for temperature sensor (DS18B20 or MLX90614)
#define LED_PIN 2       // Pin for LED
#define UDP_PORT 12345  // UDP Port for communication

WiFiUDP udp;
char incomingPacket[255];  // Buffer to hold incoming UDP packet

// IP address of Bear 2 (change this to Bear 2's IP)
IPAddress bear2IP(192, 168, 1, 2); 

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  udp.begin(UDP_PORT);  // Start listening on the UDP port
  Serial.println("UDP Server started");
}

void loop() {
  int packetSize = udp.parsePacket();  // Check if there's an incoming packet
  if (packetSize) {
    udp.read(incomingPacket, packetSize);  // Read the packet into incomingPacket buffer
    String msg = String(incomingPacket);
    
    // If the message is "HUG", light up Bear 1's LED
    if (msg == "HUG") {
      digitalWrite(LED_PIN, HIGH);
      delay(3000);  // Keep the LED on for 3 seconds
      digitalWrite(LED_PIN, LOW);
    }
  }

  // Simulate temperature reading (replace with actual sensor code)
  float temp = analogRead(TEMP_PIN) / 10.0;  // Simulating temperature reading
  
  if (temp > 30) {  // Threshold for detecting a hug
    // Send "HUG" message to Bear 2
    udp.beginPacket(bear2IP, UDP_PORT);
    udp.write("HUG");  // Send the "HUG" message
    udp.endPacket();   // Send the packet
    delay(1000);       // Prevent multiple sending too quickly
  }
}
