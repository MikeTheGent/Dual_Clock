
#include <TFT_eSPI.h>
#include "EnvironmentDisplay.h"

namespace EnvironmentDisplay {
    namespace {
        TFT_eSPI tft = TFT_eSPI();
        const uint8_t backlightChannel = 1;
        const uint8_t backlightPin = TFT_BL;
        const GFXfont *largeFont = &FreeSerif18pt7b;
        const GFXfont *smallFont = &FreeSerif12pt7b;
        const uint16_t backgroundColour = TFT_BLACK;
        const uint16_t foregroundColour = TFT_YELLOW;
    }

    void begin() {
        tft.init();
        tft.setRotation(1);
        tft.fillScreen(backgroundColour);

        ledcSetup(backlightChannel, 5000, 8);
        ledcAttachPin(backlightPin, backlightChannel);
        ledcWrite(backlightChannel, 128);

        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(largeFont);

        tft.setCursor(10, 34);
        tft.print("Temperature");
        tft.setCursor(10, 74);
        tft.print("Humidity");
        tft.setCursor(10, 114);
        tft.print("Light");
        tft.setCursor(10, 154);
        tft.print("GPS Fixes");

        displayTemperature(23.5);
        displayHumidity(55);
        displayLight(21.2);
        displayFixes(4);
    }

    void displayTime(const struct tm *clockTime) {

    }

    void displayTemperature(float temperature) {
        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(220, 34);
        tft.printf("%.1f", temperature);
    }
    
    void displayHumidity(long humidity) {
        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(220, 74);
        tft.printf("%d%%", humidity);
    }

    void displayLight(float light) {
        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(220, 114);
        tft.printf("%.2f", light);
    }

    void displayFixes(int fixes) {
        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(220, 154);
        tft.printf("%d", fixes);
    }
    
    void displayStatus(const char *message) {
    }

    void clearStatus() {
    }
}
