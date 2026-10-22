#pragma once

#include <WebServer.h>

// Serves the separate HTML/CSS/JS files stored on the LittleFS partition (data/).
class StaticContentController {
public:
    explicit StaticContentController(WebServer& server);

    bool begin();
    void registerRoutes();

private:
    void handleIndex();
    void handleNotFound();

    WebServer& server_;
};
