# ESP32_Hugging_LED_Bears
### TCP Communication

This project involves two ESP32s communicating over TCP. Each bear contains an ESP32, a temperature sensor, and LEDs. When one bear is hugged (i.e., body heat is detected), the other bear's LEDs light up in response. This is achieved using TCP communication between the ESP32s.

## Components Required:
- 2x ESP32
- 1x Temperature sensor (e.g., DS18B20 or MLX90614)
- 2x LEDs (connected to GPIO pins)
- Wi-Fi network

## Setup Instructions:
1. **Download the Code**:
   - Clone or download this repository to get the Arduino code for Bear 1 and Bear 2.

2. **Connect Components**:
   - Connect the temperature sensor to the ESP32.
   - Connect an LED to the GPIO pin on the ESP32 for visual feedback.

3. **Configure Wi-Fi**:
   - Replace `"YourSSID"` and `"YourPassword"` in the code with your Wi-Fi credentials.

4. **Configure IP Address**:
   - Get the IP address of **Bear 1** by printing `WiFi.localIP()` in the setup section of the Bear 1 code.
   - Replace the `"SERVER_IP"` in **Bear 2** with the IP address of Bear 1.

5. **Upload the Code**:
   - Upload the Bear 1 code to the first ESP32 and Bear 2 code to the second ESP32 using the Arduino IDE.

6. **Test**:
   - When you hug either bear, the other bear's LED should light up.

## Code Explanation:
- **Bear 1 (Server)** listens for connections from Bear 2 and responds to the "HUG" signal by lighting up its LED.
- **Bear 2 (Client)** sends a "HUG" signal to Bear 1 when a hug is detected and listens for the "HUG" signal from Bear 1 to light up its LED.

## License:
This project is open-source and available under the MIT License.

