
#pragma once

namespace AlexaControl {
    typedef void (*displayChangeCallback)(bool, unsigned char value);
    void begin(const char *deviceName, displayChangeCallback callback);
    void setDisplayChangeCallback(displayChangeCallback);
    void loop(void);
}

