
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ArduinoNmeaParser.h>
#include <Timezone.h>
#include "TimeSource.h"

namespace TimeSource {
    namespace {
        TimeChangeRule bstRule = {"BST", Last, Sun, Mar, 1, 60};
        TimeChangeRule gmtRule = {"GMT", Last, Sun, Oct, 2, 0};
        Timezone UK(bstRule, gmtRule);

        SoftwareSerial *gps;
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

    void begin(int8_t rxPin, int8_t txPin) {
        gps = new SoftwareSerial(rxPin, txPin);
        gps->begin(9600);
        gps->write("$PMTK220,1000*1F\r\n");
        gps->write("$PMTK314,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
    }

    void setTimeChangeCallback(timeChangeCallback callback) {
        onTimeChange = callback;
    }

    void loop(void) {
        while (gps->available() > 0) {
            byte gpsData = gps->read();
            parser.encode(gpsData);
            Serial.write(gpsData);
        }
    }
}
