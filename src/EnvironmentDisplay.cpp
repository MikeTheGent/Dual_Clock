
#include <TFT_eSPI.h>
#include "EnvironmentDisplay.h"

namespace EnvironmentDisplay {
    namespace {
        TFT_eSPI tft = TFT_eSPI();
        const uint8_t backlightChannel = 1;
        const uint8_t backlightPin = TFT_BL;
        const GFXfont *largeFont = &FreeSerif18pt7b;
        const GFXfont *smallFont = &FreeSerif12pt7b;
        const uint8_t clockFont = 7;
        const uint16_t backgroundColour = TFT_BLACK;
        const uint16_t foregroundColour = TFT_YELLOW;
    }

    void begin() {
        tft.init();
        tft.setRotation(1);
        tft.fillScreen(backgroundColour);

        ledcSetup(backlightChannel, 5000, 8);
        ledcAttachPin(backlightPin, backlightChannel);
        ledcWrite(backlightChannel, 64);

        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(largeFont);

        tft.setCursor(10, 34);
        tft.print("Temperature");
        tft.setCursor(10, 74);
        tft.print("Humidity");
        tft.setCursor(10, 114);
        tft.print("Light");
        tft.setCursor(10, 154);
        tft.print("GPS Status");

        displayTemperature(0.0);
        displayHumidity(0);
        displayBrightness(0);
        displayGpsStatus(false);
    }

    void displayTime(const struct tm *clockTime) {
        tft.setTextFont(clockFont);


    }

    void displayTemperature(float temperature) {
        tft.fillRect(220, 9, 99, 34, backgroundColour);
        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(220, 34);
        tft.printf("%.1f", temperature);
    }
    
    void displayHumidity(long humidity) {
        tft.fillRect(220, 49, 99, 34, backgroundColour);
        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(220, 74);
        tft.printf("%d%%", humidity);
    }

    void displayBrightness(long light) {
        tft.fillRect(220, 89, 99, 34, backgroundColour);
        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(220, 114);
        tft.printf("%d", light);
    }

    void displayGpsStatus(bool gpsStatus) {
        tft.fillRect(220, 129, 99, 34, backgroundColour);
        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(largeFont);
        tft.setCursor(220, 154);

        if (gpsStatus)
            tft.print("Valid");
        else
            tft.print("Invalid");
    }
    
    void displayMessage(const char *message) {
        tft.setTextColor(foregroundColour, backgroundColour);
        tft.setFreeFont(smallFont);

        
    }

    void clearMessage() {
    }

    void switchDisplay(bool state, unsigned char value) {
        if (state) {
            ledcWrite(backlightChannel, map(value, 1, 254, 1, 255));
        }
        else {
            ledcWrite(backlightChannel, 0);
        }
    }
}
