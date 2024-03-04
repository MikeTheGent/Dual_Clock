
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
static bool connectWiFi(void);

static const char *alexaDeviceName = "Dual Clock";
static unsigned long lastUpdate = 0;
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
    if (connected)
        AlexaControl::loop();

    TimeSource::loop();

    /*
    ** If we haven't had a time update for 3 minutes, something's wrong.
    */

    if (millis() > lastUpdate + 180000) {
        ClockDisplay::displayError(8);
        EnvironmentDisplay::displayMessage("No GPS time received");
    }
}

void onTimeChange(bool isValid, const struct tm *clockTime) {
    ClockDisplay::displayTime(clockTime);
    EnvironmentDisplay::displayTime(clockTime);
    lastUpdate = millis();

    EnvironmentDisplay::displayTemperature(Sensors::getTemperature());
    EnvironmentDisplay::displayHumidity(Sensors::getHumidity());
    EnvironmentDisplay::displayBrightness(Sensors::getBrightness());
    EnvironmentDisplay::displayGpsStatus(isValid);
}

void onDisplayChange(bool state, unsigned char value) {
    Serial.printf("Display state: %d, value %d\n", state, value);
    EnvironmentDisplay::switchDisplay(state, value);
    ClockDisplay::switchDisplay(state, value);
}

