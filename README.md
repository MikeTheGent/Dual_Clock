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

1. Waveshare ESP32 S3 Zero
2. Neo 7M GPS receiver, external antenna option useful to get a signal indoors
3. HT16K33 4 digit LED display
4. 320x170 TFT display
5. BH1750 light sensor (currently does nothing)
6. ClosedCube HDC1080 temperature & humidity sensor
7. Adafruit Perma-Proto Small Mint Tin Size Breadboard PCB
8. Female headers

In UK I buy parts from thepihut.com and eBay. The ClosedCube HDC1080 might be difficult
to source outside UK and can be easily substituted with other I2C sensors. Just avoid the
hopelessly inaccurate DHT11. Edit Sensors.cpp to suit your sensor.

## WiFi & Alexa

Dual Clock uses the WiFiManager library to get WiFi credentials obviating the need for hard 
coded SSID & password.

By default, the clock connects to WiFi and emulates a Phillips bulb using the fauxmoESP
library. The brightness can be adjusted and the displays turned off using Alexa. This
feature can be easily removed in main.cpp.

## Case

![Dual Clock Case](https://github.com/MikeTheGent/Dual_Clock/blob/main/resources/Dual_Clock_case_1.jpeg "Dual Clock Case")

![Dual Clock Case](https://github.com/MikeTheGent/Dual_Clock/blob/main/resources/Dual_Clock_case_2.jpeg "Dual Clock Case")

I have designed & prototyped a 3D printed open frame case. I will upload files 
here once I have completed my clock and am satisfied the case has room for everything.

## TFT_eSPI configutation

Move docs/User_Setup.h to your TFT_eSPI directory which will be somwhere in .pio/libdeps.
You will need to edit this file to suit your MCU & TFT unless you are using exactly 
the same devices as me.
