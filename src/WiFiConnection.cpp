/*
** WiFi connection manager. Uses the WiFiConnection library to avoid having hard coded
** WiFi credentials. The WiFi connection is used by the Alexa Control and could be
** omitted if that is not required.
*/

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
