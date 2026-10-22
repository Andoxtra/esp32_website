#include "ApiController.h"

#include "../core/PinJsonSerializer.h"

ApiController::ApiController(WebServer& server, PinService& pins)
    : server_(server), pins_(pins) {}

void ApiController::registerRoutes() {
    server_.on("/api/pins",        HTTP_GET,  [this] { handleListPins(); });
    server_.on("/api/pins/toggle", HTTP_POST, [this] { handleTogglePin(); });
    server_.on("/api/pins/set",    HTTP_POST, [this] { handleSetPin(); });
}

void ApiController::handleListPins() {
    sendPins();
}

void ApiController::handleTogglePin() {
    if (!server_.hasArg("id")) return sendError(400, "missing id");
    if (!pins_.toggle(server_.arg("id"))) return sendError(404, "unknown pin");
    sendPins();
}

void ApiController::handleSetPin() {
    if (!server_.hasArg("id") || !server_.hasArg("high")) return sendError(400, "missing id or high");
    const bool high = server_.arg("high") == "1";
    if (!pins_.set(server_.arg("id"), high)) return sendError(404, "unknown pin");
    sendPins();
}

void ApiController::sendPins(int statusCode) {
    server_.send(statusCode, "application/json", PinJsonSerializer::toJson(pins_));
}

void ApiController::sendError(int statusCode, const char* message) {
    server_.send(statusCode, "application/json", String("{\"error\":\"") + message + "\"}");
}
