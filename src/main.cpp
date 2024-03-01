
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
    Wire.begin(12, 13);
    Serial.begin(115200);
    ClockDisplay::begin();
    EnvironmentDisplay::begin();
    Sensors::begin();
    TimeSource::begin(13, 15);
    TimeSource::setTimeChangeCallback(onTimeChange);

    /*
    ** Connect WiFi after initialising everything else so the clock is working
    ** while WiFi spends a few seconds connecting.
    */

    connected = WiFiConnection::begin("DualClock", "DualPassword");
    Serial.printf("Connected: %d\n", connected);

    if (connected) {
        AlexaControl::begin(alexaDeviceName);
        AlexaControl::setDisplayChangeCallback(onDisplayChange);
    }
}

void loop() {
    /*
    ** Only until TimeSource is implemented...
    */

    if (millis() % 10000 == 0) {
        EnvironmentDisplay::displayTemperature(Sensors::getTemperature());
        EnvironmentDisplay::displayHumidity(Sensors::getHumidity());
        EnvironmentDisplay::displayBrightness(Sensors::getBrightness());
        struct tm clockTime;
        clockTime.tm_hour = rand() % 24;
        clockTime.tm_min = rand() % 60;
        ClockDisplay::updateTime(&clockTime);
    }

    if (connected)
        AlexaControl::loop();

    /*
    TimeSource::loop();

    ** If we haven't had a time update for 3 minutes, something's wrong.

    if (millis() > lastUpdate + 3000)
        ClockDisplay::indicateError();
    */
}

void onTimeChange(bool isValid, const struct tm *clockTime) {
    ClockDisplay::updateTime(clockTime);
    lastUpdate = millis();

    EnvironmentDisplay::displayTemperature(Sensors::getTemperature());
    EnvironmentDisplay::displayHumidity(Sensors::getHumidity());
    EnvironmentDisplay::displayBrightness(Sensors::getBrightness());
    EnvironmentDisplay::displayGpsStatus(isValid);
}

void onDisplayChange(bool state, unsigned char value) {
    Serial.printf("Display state: %d, value %d\n", state, value);
    //EnvironmentDisplay::
    ClockDisplay::switchDisplay(state, value);
}

