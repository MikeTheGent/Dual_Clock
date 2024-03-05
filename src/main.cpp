
#include <Arduino.h>
#include <Wire.h>
#include "ClockDisplay.h"
#include "EnvironmentDisplay.h"
#include "AlexaControl.h"
#include "TimeSource.h"
#include "WiFiConnection.h"
#include "Sensors.h"

void onTimeChange(bool isValid, const struct tm *clockTime);
void onDisplayChange(bool state, unsigned char value);
void IRAM_ATTR onEnvironmentTimer(void);
static void updateEnvironment(void);

static const char *alexaDeviceName = "Dual Clock";
static unsigned long lastTimeUpdate = 0;
static unsigned long nextSensorUpdate = 0;
static bool connected = false;

void setup() {
    Serial.begin(115200);
    Wire.begin(12, 13);

    ClockDisplay::begin();
    EnvironmentDisplay::begin();
    Sensors::begin();

    TimeSource::begin(7, 8);
    TimeSource::setTimeChangeCallback(onTimeChange);

    /*
    ** Connect WiFi after initialising everything else so the clock is working
    ** while WiFi spends a few seconds connecting.
    */

    connected = WiFiConnection::begin("DualClock", "DualPassword");

    if (connected) {
        AlexaControl::begin(alexaDeviceName);
        AlexaControl::setDisplayChangeCallback(onDisplayChange);
    }
}

void loop() {
    if (millis() > nextSensorUpdate) {
        updateEnvironment();
        nextSensorUpdate = millis() + 10000;
    }

    if (connected)
        AlexaControl::loop();

    TimeSource::loop();

    /*
    ** If we haven't had a time update for 3 minutes, something's wrong.
    */

    if (millis() > lastTimeUpdate + 180000) {
        ClockDisplay::displayError(8);
        EnvironmentDisplay::displayMessage("No GPS time received");
    }
}

void onTimeChange(bool isValid, const struct tm *clockTime) {
    ClockDisplay::displayTime(clockTime);
    EnvironmentDisplay::displayTime(clockTime);
    lastTimeUpdate = millis();
    EnvironmentDisplay::displayGpsStatus(isValid);
}

void onDisplayChange(bool state, unsigned char value) {
    EnvironmentDisplay::switchDisplay(state, value);
    ClockDisplay::switchDisplay(state, value);
}

static void updateEnvironment() {
    EnvironmentDisplay::displayTemperature(Sensors::getTemperature());
    EnvironmentDisplay::displayHumidity(Sensors::getHumidity());
    EnvironmentDisplay::displayBrightness(Sensors::getBrightness());
}

