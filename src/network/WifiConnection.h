#pragma once

#include <Arduino.h>

// Connects to Wi-Fi as station; falls back to an access point on failure.
class WifiConnection {
public:
    WifiConnection(const char* ssid, const char* password, unsigned long timeoutMs,
                   const char* apSsid, const char* apPassword);

    void begin();
    String ipAddress() const;

private:
    bool connectAsStation();
    void startAccessPoint();

    const char*   ssid_;
    const char*   password_;
    unsigned long timeoutMs_;
    const char*   apSsid_;
    const char*   apPassword_;
};
