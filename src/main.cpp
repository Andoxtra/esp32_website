#include <Arduino.h>

#include "Config.h"
#include "core/PinService.h"
#include "hardware/ArduinoDigitalOutput.h"
#include "network/WifiConnection.h"
#include "web/WebApplication.h"

// Composition root: wires concrete implementations to the abstractions.
namespace {

ArduinoDigitalOutput led(Config::LED_PIN);
ArduinoDigitalOutput relay(Config::RELAY_PIN);
ArduinoDigitalOutput output(Config::OUTPUT_PIN);

PinService pinService;

WifiConnection wifi(Config::WIFI_SSID, Config::WIFI_PASSWORD, Config::WIFI_CONNECT_TIMEOUT_MS,
                    Config::AP_SSID, Config::AP_PASSWORD);

WebApplication webApp(Config::HTTP_PORT, pinService);

void registerPins() {
    pinService.registerOutput("led",    "Onboard LED", Config::LED_PIN,    led);
    pinService.registerOutput("relay",  "Relay",       Config::RELAY_PIN,  relay);
    pinService.registerOutput("output", "Output",      Config::OUTPUT_PIN, output);
    pinService.beginAll();
}

}  // namespace

void setup() {
    Serial.begin(Config::SERIAL_BAUD);

    registerPins();
    wifi.begin();

    if (!webApp.begin()) {
        Serial.println("Failed to mount filesystem - did you run 'Upload Filesystem Image'?");
        return;
    }
    Serial.println("Open http://" + wifi.ipAddress());
}

void loop() {
    webApp.loop();
}
