
#pragma once 

namespace EnvironmentDisplay {
    void begin();
    void displayTime(const struct tm *clockTime);
    void displayTemperature(float temperature);
    void displayHumidity(long humidity);
    void displayStatus(const char *message);
}
