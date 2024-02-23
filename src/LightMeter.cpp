
#include <hp_BH1750.h>
#include "LightMeter.h"

namespace LightMeter {
    namespace {
        hp_BH1750 bh1750;
    }

    bool begin() {
        return bh1750.begin(BH1750_TO_GROUND);
    }

    float getLux() {
        bh1750.start();
        return bh1750.getLux();
    }
}
