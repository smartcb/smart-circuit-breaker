/*
 * This example shows how to read the energy data of a PZEM004Tv3
 *
 * The circuit:
 * - PZEM004Tv3 connected to Serial1 (RX=14, TX=27)
 *
 * Compile with -D MYCILA_JSON_SUPPORT to enable JSON support
 * Add ArduinoJson library to your project
 */
#include <Arduino.h>
#include <ArduinoJson.h>
#include <MycilaPZEM004Tv3.h>
#include <TFT_eSPI.h>
#include "constants.h" // Include constants file
#include "TFTDisplay.h"

Mycila::PZEM pzem1;
Mycila::PZEM pzem2;
Mycila::PZEM pzem3;

// TFTDisplay instance
TFT_eSPI tft = TFT_eSPI();
TFTDisplay display(tft);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    continue;

  // Initialize TFT display
  display.initialize();

  pzem1.begin(Serial1, 14, 27, 0x01, true);
  pzem2.begin(Serial1, 14, 27, 0x02, true);
  pzem3.begin(Serial1, 14, 27, 0x03, true);
}

void loop()
{
  delay(2000);
  if (pzem1.isEnabled())
  {
    JsonDocument doc;
    pzem1.toJson(doc.to<JsonObject>());

    Serial.printf("0x%02X ", pzem1.getDeviceAddress());

    serializeJson(doc, Serial);
    Serial.println();
    display.displayValues(0, doc); // Display in section 0
  }
  if (pzem2.isEnabled())
  {
    JsonDocument doc;
    pzem2.toJson(doc.to<JsonObject>());

    Serial.printf("0x%02X ", pzem2.getDeviceAddress());
    serializeJson(doc, Serial);
    Serial.println();
    display.displayValues(1, doc); // Display in section 1
  }
  if (pzem3.isEnabled())
  {
    JsonDocument doc;
    pzem3.toJson(doc.to<JsonObject>());
    Serial.printf("0x%02X ", pzem3.getDeviceAddress());
    serializeJson(doc, Serial);
    Serial.println();
    display.displayValues(2, doc); // Display in section 2
  }
}