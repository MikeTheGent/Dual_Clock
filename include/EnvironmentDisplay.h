
#pragma once 

namespace EnvironmentDisplay {
    void begin();
    void displayTime(const struct tm *clockTime);
    void displayTemperature(float temperature);
    void displayHumidity(long humidity);
    void displayBrightness(long light);
    void displayGpsStatus(bool gpsStatus);
    void displayMessage(const char *message);
    void clearMessage(void);
    void switchDisplay(bool state, unsigned char value);
}
