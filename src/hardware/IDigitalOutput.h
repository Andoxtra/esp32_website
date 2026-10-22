#pragma once

// Abstraction of a single digital output. The rest of the application
// depends only on this interface, never on Arduino/ESP32 specifics.
class IDigitalOutput {
public:
    virtual ~IDigitalOutput() = default;

    virtual void begin() = 0;
    virtual void write(bool high) = 0;
    virtual bool isHigh() const = 0;
};
