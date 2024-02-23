
#include <TFT_eSPI.h>
#include "EnvironmentDisplay.h"

namespace EnvironmentDisplay {
    namespace {
        TFT_eSPI tft = TFT_eSPI();
        const uint8_t backlightChannel = 1;
        const uint8_t backlightPin = TFT_BL;
        const GFXfont *largeFont = &FreeSerif18pt7b;
        const GFXfont *smallFont = &FreeSerif12pt7b;

    }

    void begin() {
        tft.init();
        tft.setRotation(1);
        tft.fillScreen(TFT_BLACK);

        ledcSetup(backlightChannel, 5000, 8);
        ledcAttachPin(backlightPin, backlightChannel);
        ledcWrite(backlightChannel, 64);

        tft.setTextDatum(TL_DATUM);
    }

    void displayTime(const struct tm *clockTime) {

    }

    void displayTemperature(float temperature) {
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        tft.setFreeFont(largeFont);
        tft.setCursor(10, 10);
        tft.printf("%.1f", temperature);
    }
    
    void displayHumidity(long humidity) {
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        tft.setFreeFont(largeFont);
        tft.setCursor(10, 160);
        tft.printf("%d%%", humidity);
    }
    
    void displayStatus(const char *message) {

    }
}
