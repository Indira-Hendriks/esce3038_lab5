# ESP32 WiFi LCD Display

## Project Overview
This project demonstrates how to connect an **ESP32** to a **Wi-Fi network** and retrieve data from an API using HTTPS requests. The received data is then displayed on an **I2C LCD screen**. 

## Features
- **Wi-Fi Connectivity**: Connects to a network, including support for **Wokwi simulation**.
- **Secure API Requests**: Uses **WiFiClientSecure** for HTTPS communication.
- **LCD Display**: Displays messages received from the API.
- **Error Handling**: Handles Wi-Fi disconnection, HTTP errors, and JSON parsing issues.

---

## Code Breakdown

### `setup()`
Initializes hardware components and establishes a **Wi-Fi connection**.
- **Starts Serial Communication** at 115200 baud.
- **Initializes the LCD** and displays "Connecting...".
- **Connects to Wi-Fi**:
  - Uses `WiFi.begin(SSID, PASS, 6);` for Wokwi.
  - Retries connection up to **20 times** before failing.
- **Configures HTTPS Client** (`client.setInsecure();`).
- Displays "WiFi Connected!" upon success or "WiFi Failed!" if unsuccessful.

### `loop()`
Handles the API request and updates the LCD.
- **Checks Wi-Fi Status** and reconnects if necessary.
- **Sends an HTTPS GET request** to the API.
- **Parses the JSON Response**:
  - Extracts `line_1` and `line_2` (or displays "No Data").
- **Displays the Response on the LCD**.
- **Handles Errors**:
  - If Wi-Fi disconnects, attempts reconnection.
  - If API request fails, prints the HTTP error code.
  - If JSON parsing fails, displays an error message on the LCD.

---

## How to Use
1. **Update `env.h` with your Wi-Fi credentials and API Key**:
   ```cpp
   #define SSID "your_wifi_ssid"
   #define PASS "your_wifi_password"
   #define API_KEY "your_api_key"
   #define ENDPOINT "https://your-api-endpoint.com"
   ```
2. **Upload the code to an ESP32**.
3. **Ensure the ESP32 is connected to Wi-Fi**.
4. **Check the LCD display** for messages retrieved from the API.


## Example output:

---

## Riddle: 🧠



