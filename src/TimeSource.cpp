/*
** Source of accurate time. Uses a GPS receiver to get the time from an atomic clock,
** so probably the most accurate time avaiable to the public. The time received will 
** be UTC and can be converted to local time by editing the time change rules below.
**
** (C) 2024, Mike Wilson. MIT License -- see LICENSE file included in the distribution.
*/

#include <Arduino.h>
#include <HardwareSerial.h>
#include <ArduinoNmeaParser.h>
#include <Timezone.h>
#include "TimeSource.h"

namespace TimeSource {
    namespace {
        TimeChangeRule bstRule = {"BST", Last, Sun, Mar, 1, 60};
        TimeChangeRule gmtRule = {"GMT", Last, Sun, Oct, 2, 0};
        Timezone UK(bstRule, gmtRule);

        HardwareSerial gps(1);
        timeChangeCallback onTimeChange = NULL;

        void onRmcUpdate(const nmea::RmcData rmc) {
            static int previousMinute = -1;

            if (rmc.time_utc.minute != previousMinute) {
                previousMinute = rmc.time_utc.minute;
                time_t utcTime = toPosixTimestamp(rmc.date, rmc.time_utc);
                time_t localSecs = UK.toLocal(utcTime);
                struct tm *clockTime = localtime(&localSecs);

                if (onTimeChange != NULL)
                    (onTimeChange)(rmc.is_valid, clockTime);
            }
        }

        void onGgaUpdate(const nmea::GgaData gga) {
        }

        ArduinoNmeaParser parser(onRmcUpdate, onGgaUpdate);
    }

    void begin(int8_t rxPin, int8_t txPin, timeChangeCallback callback) {
        gps.begin(9600, SERIAL_8N1, rxPin, txPin);
        gps.write("$PMTK220,1000*1F\r\n");
        gps.write("$PMTK314,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
        onTimeChange = callback;
    }

    void loop() {
        while (gps.available() > 0) {
            byte gpsData = gps.read();
            parser.encode(gpsData);
        }
    }
}
