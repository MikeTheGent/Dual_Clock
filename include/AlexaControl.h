
#pragma once

namespace AlexaControl {
    typedef void (*displayChangeCallback)(bool, unsigned char value);
    void begin(void);
    void setDisplayChangeCallback(displayChangeCallback);
    void loop(void);
}

