
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <hp_BH1750.h>
#include "LightMeter.h"

static TFT_eSPI tft = TFT_eSPI();
static hp_BH1750 bh1750;

static const uint8_t backlightChannel = 1;
static const uint8_t backlightPin = TFT_BL;
static const GFXfont *largeFont = &FreeSerif18pt7b;
static const GFXfont *smallFont = &FreeSerif12pt7b;

void setup() {
    Wire.begin(17, 18);
    Serial.begin(115200);

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    ledcSetup(backlightChannel, 5000, 8);
    ledcAttachPin(backlightPin, backlightChannel);
    ledcWrite(backlightChannel, 64);

    tft.setTextDatum(L_BASELINE);

    //tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    //tft.setCursor(10, 120);
    //tft.setFreeFont(largeFont);
    //tft.print("Time 18:45 GMT");

    //tft.setTextColor(TFT_ORANGE, TFT_BLACK);
    //tft.setCursor(10, 160);
    //tft.setFreeFont(smallFont);

    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setFreeFont(largeFont);
    tft.setCursor(10, 120);

    if (LightMeter::begin()) {
        tft.print("BH1750 connected");
    }
    else {
        tft.print("BH1750 not found");
    }

    tft.setCursor(10, 30);
    tft.print("Light level");
}

void loop() {
    if (millis() % 1000 == 0) {
        float lux = LightMeter::getLux();
        tft.setCursor(180, 30);
        tft.fillRect(180, 00, 140, 40, TFT_BLACK);
        tft.printf("%.2f", lux);

        /*
        environment.read(false);
        environment.getTemperature()
        environment.getHumidity()
        */
    }
}
