#pragma once

// Central place for all user-adjustable settings.
namespace Config {

constexpr char WIFI_SSID[]     = "testing";
constexpr char WIFI_PASSWORD[] = "12345678";
constexpr unsigned long WIFI_CONNECT_TIMEOUT_MS = 15000;

// Fallback access point if the station connection fails.
constexpr char AP_SSID[]     = "ESP32-GPIO";
constexpr char AP_PASSWORD[] = "12345678";  // min. 8 characters

constexpr unsigned short HTTP_PORT = 80;
constexpr unsigned long  SERIAL_BAUD = 115200;

// Output pins exposed to the website.
// Avoid strapping/flash pins (0, 6-11, 12, 15) and input-only pins (34-39).
constexpr int LED_PIN    = 2;   // onboard LED on most devkits
constexpr int RELAY_PIN  = 4;
constexpr int OUTPUT_PIN = 16;

}  // namespace Config
