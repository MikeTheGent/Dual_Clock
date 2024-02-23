
#pragma once

namespace TimeSource {
    typedef void (*timeChangeCallback)(const struct tm *clockTime);
    void begin(int8_t rxPin, int8_t txPin);
    void setTimeChangeCallback(timeChangeCallback);
    void parse(void);
}

