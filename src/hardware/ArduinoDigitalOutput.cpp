#include "ArduinoDigitalOutput.h"

#include <Arduino.h>

ArduinoDigitalOutput::ArduinoDigitalOutput(int pinNumber) : pin_(pinNumber) {}

void ArduinoDigitalOutput::begin() {
    pinMode(pin_, OUTPUT);
    write(false);  // always start in a defined state
}

void ArduinoDigitalOutput::write(bool high) {
    high_ = high;
    digitalWrite(pin_, high ? HIGH : LOW);
}

bool ArduinoDigitalOutput::isHigh() const {
    return high_;
}

int ArduinoDigitalOutput::pinNumber() const {
    return pin_;
}
