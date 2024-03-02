
#include <WiFiManager.h>
#include "WiFiConnection.h"

namespace WiFiConnection {
    namespace {
        bool connected = false;

        static bool initWiFi(const char *name, const char *password) {
            WiFiManager wm;
            wm.setDebugOutput(true);
            connected = wm.autoConnect(name, password);

            return connected;
        }
    }

    bool begin(const char *name, const char *password) {
        connected = initWiFi(name, password);
        return connected;
    }

    bool isConnected() {
        return connected;
    }
}
