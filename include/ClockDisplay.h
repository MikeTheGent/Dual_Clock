
#pragma once

namespace ClockDisplay {
    void begin(void);
    void updateTime(short hour, short minute);
    void adjustBrightness(short brightness);
    void switchDisplay(bool state, unsigned char value);
    void indicateError();
}
