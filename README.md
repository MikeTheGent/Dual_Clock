# Dual_Clock

**This is a work in progress although I have a working clock.**

 Clock with two displays -- a big red HT16K33 which is easy to read from many angles and a
 smaller TFT to display temperature, humidity etc. The clock uses a Neo 7M GPS receiver
 to get a very accurate time.

 The clock is still in developent and not all features are complete. At the moment,
 accurate time is displayed once the GPS receiver has a fix.

 The time zone info in TimeSource.cpp can be edited to suit different time zones.

 I have designed a 3D printed open frame case for the clock. STL files will be
 available later.

 Many mods are possible to suit different hardware.

 The version I am building uses a Waveshare ESP32 S3 Zero MCU. This is slight
 overkill, but it a nice smallpackage. The code could probably be made to work
 in a much cheaper D1 Mini with an ESP8266.

 Much more info to follow. Questions welcome.

## Compiling

The code is written in, and designed for, vscode & PlatformIO. 

## Hardware

Waveshare ESP32 S3 Zero
Neo 7M GPS receiver, external antenna option useful to get a signal indoors
HT16K33 4 digit LED display
320x170 TFT display
BH1750 light sensor (currently does nothing)
ClosedCube HDC1080 temperature & humidity sensor. Alternatives would be easy to implement.

## Alexa control

By default, the clock connected to WiFi and emulates a Phillips bulb using the fauxmoESP
library. The brightness can be adjusted and the displays turned off using Alexa. This
feature can be easily removed in main.cpp.

## WiFi

Uses the WiFiManager library to get WiFi credentials obviating the need for hard 
coded password.