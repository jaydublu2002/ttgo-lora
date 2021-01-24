/**
 * Derived from
 * https://github.com/LilyGO/TTGO-LORA32/blob/master/OLED_LoRa_Receive/OLED_LoRa_Receive.ino
 * with OLED & GPS pins amended to suit TTGO T-Beam V1.1
 * 
 * Combined with https://github.com/LilyGO/TTGO-T-Beam/blob/master/GPS/GPS.ino
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
  pinMode(16, OUTPUT);
  // T-Beam doesn't have a user LED?
  // pinMode(14,OUTPUT);

  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println();
  Serial.println("LoRa Sender Test");

  Wire.begin(i2c_sda, i2c_scl);

  int ret = axp.begin(Wire, AXP192_SLAVE_ADDRESS);

  if (ret == AXP_FAIL)
  {
    Serial.println("AXP Power begin failed");
    while (1)
      ;
  }

  SerialGPS.begin(9600, SERIAL_8N1, 34, 12); //17-TX 18-RX

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(868E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  //LoRa.onReceive(cbk);
  //  LoRa.receive();
  Serial.println("init ok");
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  delay(1500);
}

void loop()
{

  Serial.print("Latitude  : ");
  Serial.println(gps.location.lat(), 5);
  Serial.print("Longitude : ");
  Serial.println(gps.location.lng(), 4);
  Serial.print("Satellites: ");
  Serial.println(gps.satellites.value());
  Serial.print("Altitude  : ");
  Serial.print(gps.altitude.feet() / 3.2808);
  Serial.println("M");
  Serial.print("Time      : ");
  Serial.print(gps.time.hour());
  Serial.print(":");
  Serial.print(gps.time.minute());
  Serial.print(":");
  Serial.println(gps.time.second());
  Serial.println("**********************");

  Serial.print("Battery: ");
  Serial.print(String(axp.getBattVoltage()) + " mv");
  Serial.print(axp.isChargeing() ? " - Charging" : " - CHARGED");
  Serial.print("\r\n");

  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);

  display.drawString(0, 0, "Sending packet: ");
  display.drawString(90, 0, String(counter));
  display.display();

  Serial.println(String(counter));

  // send packet
  LoRa.beginPacket();
  LoRa.print(counter);
  LoRa.print(" - ");
  LoRa.print(gps.location.lat());
  LoRa.print(",");
  LoRa.print(gps.location.lng());
  LoRa.endPacket();

  counter++;

  delay(2000);
}
