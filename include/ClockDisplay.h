
#pragma once

namespace ClockDisplay {
    void begin(void);
    void displayTime(const struct tm *clockTime);
    void adjustBrightness(short brightness);
    void switchDisplay(bool state, unsigned char value);
    void displayError(int errorCode);
}
