
#include <Arduino.h>
#include <Wire.h>
#include <WiFiManager.h>
#include "ClockDisplay.h"
#include "EnvironmentDisplay.h"
#include "AlexaControl.h"
#include "TimeSource.h"
#include "WiFiConnection.h"

void onTimeChange(const struct tm *clockTime);
static bool connectWiFi();

static unsigned long lastUpdate = 0;
static bool connected = false;

void setup() {
    Wire.begin();
    Serial.begin(115200);
    ClockDisplay::begin();
    EnvironmentDisplay::begin();
    TimeSource::begin(13, 15);
    TimeSource::setTimeChangeCallback(&onTimeChange);

    /*
    ** Connect WiFi after initialising everything else so the clock is working
    ** while WiFi spends a few seconds connecting.
    */

    connected = WiFiConnection::begin();

    if (connected) {
        AlexaControl::begin();
        AlexaControl::setDisplayChangeCallback(&ClockDisplay::switchDisplay);
    }
}

void loop() {
    TimeSource::parse();

    if (connected)
        AlexaControl::loop();

    /*
    ** If we haven't had a time update for 3 minutes, something's up.
    */

    if (millis() > lastUpdate + 3000)
        ClockDisplay::indicateError();
}

void onTimeChange(const struct tm *clockTime) {
    ClockDisplay::updateTime(clockTime);
    lastUpdate = millis();
}

