
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
