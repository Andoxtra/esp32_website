#include "WebApplication.h"

WebApplication::WebApplication(unsigned short port, PinService& pins)
    : server_(port), api_(server_, pins), content_(server_) {}

bool WebApplication::begin() {
    if (!content_.begin()) return false;
    api_.registerRoutes();
    content_.registerRoutes();
    server_.begin();
    return true;
}

void WebApplication::loop() {
    server_.handleClient();
}
