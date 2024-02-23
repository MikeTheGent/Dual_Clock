
#include <Arduino.h>
#include <HT16K33.h>
#include "ClockDisplay.h"

namespace ClockDisplay {
    namespace {
        HT16K33 display(0x70);
    }

    void begin(void) {
        display.begin();
        switchDisplay(true, 1);
        display.setBlink(3);
        display.displayTime(99, 99);
    }

    /*
    ** Update the display to show the time. Arguments are assumed to be a valid time.
    */

    void updateTime(const struct tm *clockTime) {
        display.displayTime(clockTime->tm_hour,clockTime->tm_min);
        display.setBlink(0);
    }

    /*
    ** Switch the display on or off. If the display is on, adjust the brightness.
    */

    void switchDisplay(bool state, unsigned char value) {
        if (state) {
            display.displayOn();
            display.brightness(map(value, 1, 100, 0, 15));
        }
        else {
            display.displayOff();
        }
    }

    void indicateError() {
        display.setBlink(3);
        display.displayTime(88, 88);
    }
}
