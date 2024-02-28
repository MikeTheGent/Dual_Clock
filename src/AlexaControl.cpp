
#include <Arduino.h>
#include <fauxmoESP.h>
#include "AlexaControl.h"

namespace AlexaControl {
    namespace {
        fauxmoESP fauxmo;
        displayChangeCallback onDisplayChange = NULL;

        /*
        ** Callback when fauxmoESP receives an Alexa command for this device.
        */

        void clockChanged(unsigned char deviceId, const char *deviceName,
                bool state, unsigned char value) {

            if (onDisplayChange != NULL)
                (onDisplayChange)(state, value);
        }
    }

    void begin(const char *deviceName) {
        fauxmo.createServer(true);
        fauxmo.setPort(80);
        fauxmo.enable(true);
        fauxmo.addDevice(deviceName);
        fauxmo.onSetState(clockChanged);
    }


    void setDisplayChangeCallback(displayChangeCallback callback) {
        onDisplayChange = callback;
    }

    void loop(void) {
        fauxmo.handle();
    }
}
