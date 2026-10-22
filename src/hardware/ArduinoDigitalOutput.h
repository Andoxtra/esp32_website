#pragma once

#include "IDigitalOutput.h"

// IDigitalOutput implementation backed by the Arduino GPIO API.
class ArduinoDigitalOutput : public IDigitalOutput {
public:
    explicit ArduinoDigitalOutput(int pinNumber);

    void begin() override;
    void write(bool high) override;
    bool isHigh() const override;

    int pinNumber() const;

private:
    int  pin_;
    bool high_ = false;
};
