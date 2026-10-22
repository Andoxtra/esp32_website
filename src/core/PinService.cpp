#include "PinService.h"

void PinService::registerOutput(const String& id, const String& label, int gpio, IDigitalOutput& output) {
    entries_.push_back({id, label, gpio, &output});
}

void PinService::beginAll() {
    for (auto& entry : entries_) {
        entry.output->begin();
    }
}

const std::vector<PinService::Entry>& PinService::entries() const {
    return entries_;
}

bool PinService::toggle(const String& id) {
    Entry* entry = find(id);
    if (entry == nullptr) return false;
    entry->output->write(!entry->output->isHigh());
    return true;
}

bool PinService::set(const String& id, bool high) {
    Entry* entry = find(id);
    if (entry == nullptr) return false;
    entry->output->write(high);
    return true;
}

PinService::Entry* PinService::find(const String& id) {
    for (auto& entry : entries_) {
        if (entry.id == id) return &entry;
    }
    return nullptr;
}
