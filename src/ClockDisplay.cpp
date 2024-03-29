/*
** Clock display -- probably sometime big enough to be seen across a typical 
** living room. Originally designed to use a 4x7 segment display driven by a HT16K33.
**
** (C) 2024, Mike Wilson. MIT License -- see LICENSE file included in the distribution.
*/

#include <Arduino.h>
#include <HT16K33.h>
#include "ClockDisplay.h"

namespace ClockDisplay {
    namespace {
        HT16K33 display(0x70);
    }

    void begin() {
        display.begin();
        switchDisplay(true, 128);
        display.setBlink(3);
        display.displayTime(99, 99);
    }

    void displayTime(const struct tm *clockTime) {
        display.displayTime(clockTime->tm_hour, clockTime->tm_min);
        display.setBlink(0);
    }

    void switchDisplay(bool state, unsigned char value) {
        if (state) {
            display.displayOn();
            display.brightness(map(value, 4, 254, 0, 15));
        }
        else {
            display.displayOff();
        }
    }

    void displayError(int errorCode) {
        display.setBlink(3);
        display.displayTime(errorCode * 11, errorCode * 11);
    }
}
