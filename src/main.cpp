
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
static void updateEnvironment(void);

/*
** Pins used for GPS Serial and I2C for other peripherals.
*/

static const uint8_t gpsRxPin = 7;
static const uint8_t gpsTxPin = 8;
static const int i2cSDA = 12;
static const int i2cSCL = 13;

static const char *alexaDeviceName = "Dual Clock";
static unsigned long lastTimeUpdate = 0;
static unsigned long nextSensorUpdate = 0;

void setup() {
    Serial.begin(115200);
    Wire.begin(i2cSDA, i2cSCL);

    ClockDisplay::begin();
    EnvironmentDisplay::begin();
    Sensors::begin();
    TimeSource::begin(gpsRxPin, gpsTxPin, onTimeChange);

    /*
    ** Connect WiFi after initialising everything else so the clock is working
    ** while WiFi spends a few seconds connecting.
    */

    if (WiFiConnection::begin("DualClock", "DualPassword")) {
        AlexaControl::begin(alexaDeviceName, onDisplayChange);
    }
}

void loop() {
    if (millis() > nextSensorUpdate) {
        updateEnvironment();
        nextSensorUpdate = millis() + 10000;
    }

    if (WiFiConnection::isConnected()) {
        AlexaControl::loop();
    }

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
    EnvironmentDisplay::displayGpsStatus(isValid);
    lastTimeUpdate = millis();
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

