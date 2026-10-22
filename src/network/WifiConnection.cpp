#include "WifiConnection.h"

#include <WiFi.h>

WifiConnection::WifiConnection(const char* ssid, const char* password, unsigned long timeoutMs,
                               const char* apSsid, const char* apPassword)
    : ssid_(ssid), password_(password), timeoutMs_(timeoutMs),
      apSsid_(apSsid), apPassword_(apPassword) {}

void WifiConnection::begin() {
    if (!connectAsStation()) {
        Serial.println("Wi-Fi connection failed, starting access point");
        startAccessPoint();
    }
}

String WifiConnection::ipAddress() const {
    const bool isStation = WiFi.getMode() == WIFI_STA;
    return isStation ? WiFi.localIP().toString() : WiFi.softAPIP().toString();
}

bool WifiConnection::connectAsStation() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid_, password_);

    const unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - start > timeoutMs_) return false;
        delay(250);
        Serial.print('.');
    }
    Serial.println();
    return true;
}

void WifiConnection::startAccessPoint() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(apSsid_, apPassword_);
}
