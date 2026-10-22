#include "PinJsonSerializer.h"

namespace {

String escape(const String& text) {
    String out;
    for (size_t i = 0; i < text.length(); ++i) {
        const char c = text[i];
        if (c == '"' || c == '\\') out += '\\';
        out += c;
    }
    return out;
}

}  // namespace

String PinJsonSerializer::toJson(const PinService& service) {
    String json = "[";
    bool first = true;
    for (const auto& entry : service.entries()) {
        if (!first) json += ",";
        first = false;
        json += "{\"id\":\"" + escape(entry.id) + "\"";
        json += ",\"label\":\"" + escape(entry.label) + "\"";
        json += ",\"gpio\":" + String(entry.gpio);
        json += ",\"high\":" + String(entry.output->isHigh() ? "true" : "false") + "}";
    }
    json += "]";
    return json;
}
