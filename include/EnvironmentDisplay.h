
#pragma once 

namespace EnvironmentDisplay {
    void begin();
    void displayTime(const struct tm *clockTime);
    void displayTemperature(float temperature);
    void displayHumidity(long humidity);
    void displayBrightness(float light);
    void displayGpsStatus(bool gpsStatus);
    void displayMessage(const char *message);
    void clearMessage(void);
}
