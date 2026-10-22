#include "StaticContentController.h"

#include <LittleFS.h>

StaticContentController::StaticContentController(WebServer& server) : server_(server) {}

bool StaticContentController::begin() {
    return LittleFS.begin(true);  // format on first use
}

void StaticContentController::registerRoutes() {
    server_.on("/", HTTP_GET, [this] { handleIndex(); });
    server_.serveStatic("/", LittleFS, "/");  // style.css, app.js, ...
    server_.onNotFound([this] { handleNotFound(); });
}

void StaticContentController::handleIndex() {
    File file = LittleFS.open("/index.html", "r");
    if (!file) return handleNotFound();
    server_.streamFile(file, "text/html");
    file.close();
}

void StaticContentController::handleNotFound() {
    server_.send(404, "text/plain", "Not found");
}
