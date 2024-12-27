#include <WiFi.h>

#define WIFI_SSID "YourSSID"
#define WIFI_PASS "YourPassword"
#define SERVER_IP "192.168.1.XX"  // IP address of Bear 1
#define SERVER_PORT 12345         // Port of Bear 1 to connect to
#define TEMP_PIN 4                // Pin for temperature sensor (DS18B20 or MLX90614)
#define LED_PIN 2                 // Pin for LED

WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Simulate temperature reading (replace with actual sensor code)
  float temp = analogRead(TEMP_PIN) / 10.0;  // Simulating temperature reading
  
  if (temp > 30) {  // Threshold for detecting a hug
    // Connect to Bear 1
    if (client.connect(SERVER_IP, SERVER_PORT)) {
      client.println("HUG");  // Send the "HUG" message
      client.stop();          // Close the connection after sending
      Serial.println("HUG sent to Bear 1");
      delay(1000);  // Prevent multiple sends too quickly
    }
  }

  // Check for incoming signal from Bear 1
  if (client.connect(SERVER_IP, SERVER_PORT)) {
    if (client.available()) {
      String msg = client.readStringUntil('\n');
      if (msg == "HUG") {
        digitalWrite(LED_PIN, HIGH);
        delay(3000);  // Keep LED on for 3 seconds
        digitalWrite(LED_PIN, LOW);
      }
    }
    client.stop();  // Stop the connection after receiving the signal
  }
}
