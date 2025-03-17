#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>  // Secure client for HTTPS
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>  // LCD Library
#include "env.h"                // Load WiFi credentials & API info

// Define if running on Wokwi
#define IS_WOKWI true

// Initialize the LCD (I2C address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClientSecure client;  // Secure client for HTTPS requests

void setup() {
    Serial.begin(115200);

    // Initialize LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");

    // Connect to Wi-Fi with proper method for Wokwi
    if (IS_WOKWI) 
        WiFi.begin(SSID, PASS, 6);  // Channel 6 for Wokwi
    else 
        WiFi.begin(SSID, PASS);

    Serial.print("Connecting to WiFi");
    
    int retries = 20;  // Timeout after ~10 seconds
    while (WiFi.status() != WL_CONNECTED && retries > 0) {
        delay(500);
        Serial.print(".");
        retries--;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WiFi Connected!");
        delay(2000);
    } else {
        Serial.println("\nWiFi connection failed.");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WiFi Failed!");
        while (true);  // Stop execution if Wi-Fi fails
    }

    // Configure WiFiClientSecure for HTTPS
    client.setInsecure();  // Disable SSL verification (for testing)
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Disconnected. Reconnecting...");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WiFi Reconnecting...");
        WiFi.reconnect();
        delay(5000);
        return;
    }

    HTTPClient http;
    http.begin(client, ENDPOINT);  // Use HTTPS client
    http.addHeader("api-key", API_KEY);  // Add API key as required
    http.addHeader("Content-Type", "application/json");  // Add content-type

    Serial.println("Sending GET request...");
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println("Response: " + payload);

        // Parse JSON response
        DynamicJsonDocument doc(512);
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            Serial.print("JSON Parsing Failed: ");
            Serial.println(error.c_str());
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("JSON Error:");
            lcd.setCursor(0, 1);
            lcd.print(error.c_str());
        } else {
            // Extract values and check if they are null
            const char* line1 = doc["line_1"] | "No Data";
            const char* line2 = doc["line_2"] | "No Data";

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(line1);
            lcd.setCursor(0, 1);
            lcd.print(line2);
        }
    } else {
        Serial.print("HTTP Error: ");
        Serial.println(httpCode);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("HTTP Error:");
        lcd.setCursor(0, 1);
        lcd.print(httpCode);
    }

    http.end();
    delay(5000);
}

