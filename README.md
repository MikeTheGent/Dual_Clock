# Dual_Clock

**This is a work in progress although I have a working clock.**

 Clock with two displays -- a big red HT16K33 which is easy to read from many angles and a
 smaller TFT to display temperature, humidity etc. The clock uses a Neo 7M GPS receiver
 to get a very accurate time.

 The clock is still in developent and not all features are complete. At the moment,
 accurate time is displayed once the GPS receiver has a fix.

 The time zone info in TimeSource.cpp can be edited to suit different time zones.

 Many mods are possible to suit different hardware.

 The version I am building uses a Waveshare ESP32 S3 Zero MCU. This is slight
 overkill, but it a nice small package. The code could probably be made to work
 in a much cheaper D1 Mini with an ESP8266.

 Much more info to follow. Questions welcome.

## Code

As an experiment, I implemented everything using namespaces instead of classes. I'd
heard some harsh criticism of OOP and wanted to experiment with the alternatives. I
actually prefer this approach when there is only going to one instance of a thing.
The code seems to be shorter and easier to understand. Each namespace is decoupled
from the others -- everything is tied together in main.cpp.

The code is written in, and designed for, vscode & PlatformIO. A bit of moving &
renaming of main.cpp would probably be all that's needed to compile it in Arduino IDE. 
But why?

platformio.ini is configured for an adafruit_feather_esp32s3 which is the closest
I could find to the spec of my Waveshare ESP32 S3 Zero. These boards both have 4Mb RAM
unlike other S3 boards which have 8Mb. It took a while to figure out why the MCU
was crashing.

## Parts

Find the Parts List in the [Wiki](https://github.com/MikeTheGent/Dual_Clock/wiki)

## WiFi & Alexa

Dual Clock uses the WiFiManager library to get WiFi credentials obviating the need for hard 
coded SSID & password.

By default, the clock connects to WiFi and emulates a Phillips bulb using the fauxmoESP
library. The brightness can be adjusted and the displays turned off using Alexa. This
feature can be easily removed in main.cpp.

## Case

You can download my case design from the
[Wiki](https://github.com/MikeTheGent/Dual_Clock/wiki)

## TFT_eSPI configutation

Move resources/User_Setup.h to your TFT_eSPI directory which will be somwhere in 
.pio/libdeps. You will need to edit this file to suit your MCU & TFT unless you 
are using exactly the same devices as me.
