#pragma once

#include <Arduino.h>

#include "PinService.h"

// Converts the pin state to JSON (no external library needed).
namespace PinJsonSerializer {
String toJson(const PinService& service);
}
