
#pragma once

namespace TimeSource {
    typedef void (*timeChangeCallback)(bool isValid, const struct tm *clockTime);
    void begin(int8_t rxPin, int8_t txPin, timeChangeCallback callback);
    void loop(void);
}

