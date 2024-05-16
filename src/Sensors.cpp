/*
** Environment sensors. Eg, temperature, humidity, light level. Originally designed
** to use a BH1750 light sensor & ClosedCube HDC1080 temperature & humidity sensor.
** Either of these can be substituted with appropriate alternatives.
**
** (C) 2024, Mike Wilson. MIT License -- see LICENSE file included in the distribution.
*/

#include <hp_BH1750.h>
#include <ClosedCube_HDC1080.h>
#include "Sensors.h"

namespace Sensors {
    namespace {
        hp_BH1750 bh1750;
        ClosedCube_HDC1080 hdc1080;
    }

    bool begin() {
        hdc1080.begin(0x40);
        hdc1080.setResolution(HDC1080_RESOLUTION_14BIT,
            HDC1080_RESOLUTION_14BIT);
        return bh1750.begin(BH1750_TO_GROUND);
    }

    float getTemperature() {
        return float(hdc1080.readTemperature());
    }

    long getHumidity() {
        return long(hdc1080.readHumidity());
    }

    long getBrightness() {
        bh1750.start();
        return long(bh1750.getLux());
    }
}

