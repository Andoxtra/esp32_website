#pragma once

#include <WebServer.h>

#include "../core/PinService.h"

// REST API:
//   GET  /api/pins                      -> list of pins with state
//   POST /api/pins/toggle?id=<id>       -> toggle a pin
//   POST /api/pins/set?id=<id>&high=0|1 -> set a pin explicitly
class ApiController {
public:
    ApiController(WebServer& server, PinService& pins);

    void registerRoutes();

private:
    void handleListPins();
    void handleTogglePin();
    void handleSetPin();

    void sendPins(int statusCode = 200);
    void sendError(int statusCode, const char* message);

    WebServer&  server_;
    PinService& pins_;
};
