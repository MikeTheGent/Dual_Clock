
#pragma once

namespace Sensors {
    bool begin(void);
    void update(void);
    float getTemperature(void);
    long getHumidity(void);
    long getBrightness(void);
}
