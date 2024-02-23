
#include <Arduino.h>
#include <fauxmoESP.h>
#include "AlexaControl.h"

namespace AlexaControl {
    namespace {
        fauxmoESP fauxmo;
        bool initialised = false;
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

    void setDisplayChangeCallback(displayChangeCallback callback) {
        onDisplayChange = callback;
    }

    void loop(void) {
        if (! initialised) {
            fauxmo.createServer(true);
            fauxmo.setPort(80);
            fauxmo.enable(true);
            fauxmo.addDevice("Red Clock");
            fauxmo.onSetState(clockChanged);
            initialised = true;
        }

        fauxmo.handle();
    }
}

