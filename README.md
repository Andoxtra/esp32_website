# ESP32 GPIO Web Control (PlatformIO)

## Structure
- `include/Config.h`          Wi-Fi credentials, pins, port
- `src/hardware/`             `IDigitalOutput` + Arduino implementation (HAL)
- `src/core/`                 `PinService` (app logic), JSON serializer
- `src/network/`              Wi-Fi connection (station, AP fallback)
- `src/web/`                  Web server, REST API controller, static file controller
- `data/`                     `index.html`, `style.css`, `app.js` (served from LittleFS)

## Usage
1. Set Wi-Fi credentials in `include/Config.h`.
2. Upload the website files: `pio run -t uploadfs`
3. Upload the firmware:      `pio run -t upload`
4. Open the serial monitor (`pio device monitor`) and visit the printed IP.
   If Wi-Fi fails, connect to AP `ESP32-GPIO` and open http://192.168.4.1

## API
- `GET  /api/pins`
- `POST /api/pins/toggle?id=led`
- `POST /api/pins/set?id=led&high=1`
