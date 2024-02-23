
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include "TimeSource.h"
#include "ClockDisplay.h"

void onTimeChange(const struct tm *clockTime);

void setup() {
    Wire.begin(17, 18);
    Serial.begin(115200);
    TimeSource::begin(12, 11);
    ClockDisplay::begin();
    TimeSource::setTimeChangeCallback(onTimeChange);

}

void loop() {
    TimeSource::parse();
}

void onTimeChange(const struct tm *clockTime) {
    Serial.printf("%2.2d:%2.2d\n", clockTime->tm_hour,clockTime->tm_min);
    ClockDisplay::updateTime(clockTime);
}

