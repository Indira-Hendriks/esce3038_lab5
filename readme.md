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
ets Jul 29 2019 12:21:46

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:1156
load:0x40078000,len:11456
ho 0 tail 12 room 4
load:0x40080400,len:2972
entry 0x400805dc
Connecting to WiFi...
WiFi connected. IP: 10.10.0.2
Sending GET request...
Response: {"line_1":"Good","line_2":"Luck"}
Sending GET request...
HTTP Error: -1
Sending GET request...
Response: {"line_1":"Good","line_2":"Luck"}
Sending GET request...

---

## Riddle: 🧠

It has no top or bottom 
but can hold flesh, bones, and blood all at the same time.
 What is this object?

