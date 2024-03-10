# Parts list

1. Waveshare ESP32 S3 Zero
2. Neo 7M GPS receiver, external antenna option useful to get a signal indoors
3. HT16K33 4 digit LED display
4. 1.9", 170x320 pixel TFT display
5. BH1750 light sensor (currently does nothing)
6. ClosedCube HDC1080 temperature & humidity sensor
7. Adafruit Perma-Proto Small Mint Tin Size Breadboard PCB
8. Female headers
9. 10cm/4" Male to Female DuPont cables

In UK I buy parts from thepihut.com and eBay. The ClosedCube HDC1080 might be difficult
to source outside UK and can be easily substituted with other I2C sensors. Just avoid the
hopelessly inaccurate DHT11. Edit Sensors.cpp to suit your sensor.