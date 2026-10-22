#pragma once

#include <WebServer.h>

#include "../core/PinService.h"
#include "ApiController.h"
#include "StaticContentController.h"

// Composition root of the web layer: owns the server and its controllers.
class WebApplication {
public:
    WebApplication(unsigned short port, PinService& pins);

    bool begin();
    void loop();

private:
    WebServer               server_;
    ApiController           api_;
    StaticContentController content_;
};
