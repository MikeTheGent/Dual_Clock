
#include <Arduino.h>
#include <fauxmoESP.h>
#include "AlexaControl.h"

namespace AlexaControl {
    namespace {
        fauxmoESP fauxmo;
        displayChangeCallback onDisplayChange = NULL;

        void alexaCallback(unsigned char deviceId, const char *deviceName,
                bool state, unsigned char value) {

            if (onDisplayChange != NULL)
                (onDisplayChange)(state, value);
        }
    }

    void begin(const char *deviceName, displayChangeCallback callback) {
        fauxmo.createServer(true);
        fauxmo.setPort(80);
        fauxmo.enable(true);
        fauxmo.addDevice(deviceName);
        fauxmo.onSetState(alexaCallback);
        onDisplayChange = callback;
    }

    void loop(void) {
        fauxmo.handle();
    }
}
