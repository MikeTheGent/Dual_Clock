
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include "TimeSource.h"
#include "ClockDisplay.h"
#include "EnvironmentDisplay.h"

void onTimeChange(const struct tm *clockTime);

void setup() {
    Wire.begin();
    Serial.begin(115200);
    EnvironmentDisplay::begin();
    //TimeSource::begin(12, 11);
    //ClockDisplay::begin();
    //TimeSource::setTimeChangeCallback(onTimeChange);

}

void loop() {
    //TimeSource::parse();
}

void onTimeChange(const struct tm *clockTime) {
    Serial.printf("%2.2d:%2.2d\n", clockTime->tm_hour,clockTime->tm_min);
    ClockDisplay::updateTime(clockTime);
}

