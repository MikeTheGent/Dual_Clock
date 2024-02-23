
#include <WiFiManager.h>
#include "WiFiConnection.h"

namespace WiFiConnection {
    namespace {
        bool connected = false;

        static bool initWiFi() {
            WiFiManager wm;
            connected = wm.autoConnect("RedClock", "RedPassword");

            return connected;
        }
    }

    bool begin() {
        connected = initWiFi();

        return connected;
    }

    bool isConnected() {
        return connected;
    }
}
