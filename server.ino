#include <WiFi.h>

#define WIFI_SSID "YourSSID"
#define WIFI_PASS "YourPassword"
#define SERVER_PORT 12345      // Port for Bear 1 to listen on
#define TEMP_PIN 4             // Pin for temperature sensor (DS18B20 or MLX90614)
#define LED_PIN 2              // Pin for LED

WiFiServer server(SERVER_PORT);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.begin();  // Start listening for incoming connections from Bear 2
  Serial.println("Server started, waiting for client...");
}

void loop() {
  WiFiClient client = server.available();  // Check if there's a client trying to connect
  
  if (client) {
    Serial.println("Client connected.");
    // Check for incoming "HUG" signal
    while (client.connected()) {
      if (client.available()) {
        String msg = client.readStringUntil('\n');
        if (msg == "HUG") {
          digitalWrite(LED_PIN, HIGH);
          delay(3000);  // Keep the LED on for 3 seconds
          digitalWrite(LED_PIN, LOW);
        }
      }
    }
    client.stop();  // Stop the client when done
    Serial.println("Client disconnected.");
  }

  // Simulate temperature reading (replace with actual sensor code)
  float temp = analogRead(TEMP_PIN) / 10.0;  // Simulating temperature reading

  if (temp > 30) {  // Threshold for detecting a hug
    // Respond to Bear 2, telling it to light up its LEDs
    WiFiClient client = server.available();
    if (client) {
      client.println("HUG");  // Send "HUG" message to Bear 2
      delay(1000);  // Prevent spamming
    }
  }
}
