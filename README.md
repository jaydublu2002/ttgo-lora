Various PlatformIO projects exploring TTGO LoRa boards.

# References

## Hardware

### LilyGO LoRa Series

- https://github.com/Xinyuan-LilyGO/LilyGO-T-Beam - lots of exapmles and links to datasheets etc.

### TTGO LoRa32

- ESP32
- SX1276 LoRa chip
- TP4054 Battery management
- CP2102 USB interface
- SSD1306 0.96 inch 128X64  OLED
- 32MB flash
- User LED = IO25

- https://github.com/LilyGO/TTGO-LORA32
- [Schematic](https://github.com/Xinyuan-LilyGO/LilyGO-T-Beam/blob/master/schematic/T3_V1.3.pdf)

### TTGO LoRa T-Beam v1.1

- ESP32 Rev1
- NEO-6M GPS Module
- TP5400 Battery management (or AXP192?)
- CP2104-GMR USB interface
- SSD1306 0.96 inch 128X64  OLED
- 4MB PSRAM
- 4MB Flash

- [Product page](http://www.lilygo.cn/claprod_view.aspx?TypeId=62&Id=1281&FId=t28:62:28)
- https://github.com/LilyGO/TTGO-T-Beam
- [Schematic](https://github.com/LilyGO/TTGO-T-Beam/blob/master/t22_gps_v07(1).pdf)
  
## Libraries

### ESP32

- https://en.wikipedia.org/wiki/ESP32
- [API Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/)

### LoRa

- [LoRa](https://github.com/sandeepmistry/arduino-LoRa) Library
- LoRa Library [API](https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md)
- [Frequency Plans (TTN)](https://www.thethingsnetwork.org/docs/lorawan/frequency-plans.html)

### OLED - SSD1306

- ThingPulse [SSD1306Wire](https://github.com/ThingPulse/esp8266-oled-ssd1306) Library

### GPS

- [TinGPS++](https://github.com/mikalhart/TinyGPSPlus)
- [documentation](http://arduiniana.org/libraries/tinygpsplus/)

### Videos

- [#149 ESP32 Deep Sleep, RTC Memory, "Secret" LoLin Pins](https://youtu.be/r75MrWIVIw4)
- [#172 Hidden: ESP32 and ESP8266 point-to-point (ESP-Now): Fast and efficient. Comparison with LoRa](https://youtu.be/6NsBN42B80Q)
- [#188 Antenna Tutorial incl. cheap DIY Antenna Tester (LoRa, ESP32)](https://youtu.be/J3PBL9oLPX8)
- [#224 Are these boards ok? New LoRa boards tested (mainly TTGO ESP32)](https://youtu.be/cjVwTf8iDFY)
- [#252 ESP32 Ultra Low Power (ULP) core made easy in the Arduino IDE including 100$ challenge](https://youtu.be/-QIcUTBB7Ww)
- [#264 PlatformIO for Arduino, ESP8266, and ESP32 Tutorial](https://youtu.be/0poh_2rBq7E)
- [#328 ESP32 Secrets: Interrupts, and Deep-Sleep under the Hood](https://youtu.be/CJhWlfkf-5M)
- [#337 LoRa Mesh Communication without Infrastructure: The Meshtastic Project (ESP32, BLE, GPS)](https://youtu.be/TY6m6fS8bxU)
- [Which ESP32 pins are safe to use?](https://youtu.be/LY-1DHTxRAk)
- [ESP32 Pins.xlsx](https://drive.google.com/file/d/1gbKM7DA7PI7s1-ne_VomcjOrb0bE2TPZ/view)