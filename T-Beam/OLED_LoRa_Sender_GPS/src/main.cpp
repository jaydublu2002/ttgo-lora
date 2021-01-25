/**
 * Derived from
 * https://github.com/LilyGO/TTGO-LORA32/blob/master/OLED_LoRa_Receive/OLED_LoRa_Receive.ino
 * with OLED & GPS pins amended to suit TTGO T-Beam V1.1
 *
 * Combined with https://github.com/LilyGO/TTGO-T-Beam/blob/master/GPS/GPS.ino
 * And a bit of https://github.com/lewisxhe/AXP202X_Library
 */

#include <Arduino.h>
#include <axp20x.h>
#include <LoRa.h>
#include <SPI.h>
#include <SSD1306.h>
#include <TinyGPS++.h>
#include <Wire.h>

#define SCK 5   // GPIO5  -- SX1278's SCK
#define MISO 19 // GPIO19 -- SX1278's MISnO
#define MOSI 27 // GPIO27 -- SX1278's MOSI
#define SS 18   // GPIO18 -- SX1278's CS
#define RST 14  // GPIO14 -- SX1278's RESET
#define DI0 26  // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND 868E6

const uint8_t i2c_sda = 21;
const uint8_t i2c_scl = 22;

unsigned int counter = 0;
char buffer[50];

AXP20X_Class axp;
SSD1306 display(0x3c, i2c_sda, i2c_scl);
String rssi = "RSSI --";
String packSize = "--";
String packet;
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (SerialGPS.available())
      gps.encode(SerialGPS.read());
  } while (millis() - start < ms);
}

void setup()
{
  // Initialise & reset OLED
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(50);
  digitalWrite(16, HIGH);

  // Initialise serial
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println();
  Serial.println("LoRa Sender Test");

  Wire.begin(i2c_sda, i2c_scl);

  // Initialise AXP battery management
  int ret = axp.begin(Wire, AXP192_SLAVE_ADDRESS);
  if (ret == AXP_FAIL)
  {
    Serial.println("AXP Power begin failed");
    while (1)
      ;
  }

  // Initialise GPS
  SerialGPS.begin(9600, SERIAL_8N1, 34, 12);

  // Initialise LoRa
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(868E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }

  Serial.println("init ok");

  display.init();
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);

  delay(1500);
}

void loop()
{
  smartDelay(5000);

  sprintf(buffer, "%06d,%4.2f,%08.4f,%08.4f,%02d:%02d:%02d",
          counter,
          axp.getBattVoltage() / 1000,
          gps.location.lat(),
          gps.location.lng(),
          gps.time.hour(),
          gps.time.minute(),
          gps.time.second());

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

  display.clear();
  display.drawString(0, 0, buffer);
  display.display();

  Serial.println(buffer);

  LoRa.beginPacket();
  LoRa.print(buffer);
  LoRa.endPacket();

  if (counter++ == 1000000)
    counter = 0;
}
