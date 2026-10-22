#pragma once

#include <Arduino.h>
#include <vector>

#include "../hardware/IDigitalOutput.h"

// Application logic: manages named outputs and their state.
// Knows nothing about HTTP or about concrete hardware.
class PinService {
public:
    struct Entry {
        String          id;
        String          label;
        int             gpio;
        IDigitalOutput* output;
    };

    void registerOutput(const String& id, const String& label, int gpio, IDigitalOutput& output);
    void beginAll();

    const std::vector<Entry>& entries() const;

    bool toggle(const String& id);
    bool set(const String& id, bool high);

private:
    Entry* find(const String& id);

    std::vector<Entry> entries_;
};
