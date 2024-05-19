/*
** Dual Clock is a digital clock with 2 displays -- one larger intended to be read
** from across a typical living room, the other a small TFT to display environment
** information. Receives atomic clock time from a GPS module.
**
** This module initialises everything and connects up the other modules.
**
** (C) 2024, Mike Wilson. MIT License -- see LICENSE file included in the distribution.
*/

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
** Pins used for GPS Serial UART and I2C for other peripherals.
*/

static const uint8_t gpsRxPin = 7;
static const uint8_t gpsTxPin = 8;
static const int i2cSDA = 12;
static const int i2cSCL = 13;

static const char *alexaDeviceName = "Red Clock";
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

/*
** Callback from TimeSource when a time change happens. Update the clock displays.
*/

void onTimeChange(bool isValid, const struct tm *clockTime) {
    ClockDisplay::displayTime(clockTime);
    EnvironmentDisplay::displayTime(clockTime);
    EnvironmentDisplay::displayGpsStatus(isValid);
    lastTimeUpdate = millis();
}

/*
** Callback from AlexaControl when the device status changes.
*/

void onDisplayChange(bool state, unsigned char value) {
    EnvironmentDisplay::switchDisplay(state, value);
    ClockDisplay::switchDisplay(state, value);
}

/*
** Update the environment display.
*/

static void updateEnvironment() {
    EnvironmentDisplay::displayTemperature(Sensors::getTemperature());
    EnvironmentDisplay::displayHumidity(Sensors::getHumidity());
    EnvironmentDisplay::displayBrightness(Sensors::getBrightness());
}

