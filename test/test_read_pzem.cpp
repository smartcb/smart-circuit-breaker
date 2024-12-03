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

Mycila::PZEM pzem1;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    continue;

  pzem1.begin(Serial1, 14, 27, 0x01, true);
}

void loop() {
  delay(2000);
  if (pzem1.isEnabled()) {
    JsonDocument doc;
    pzem1.toJson(doc.to<JsonObject>());
    Serial.printf("0x%02X ", pzem1.getDeviceAddress());
    serializeJson(doc, Serial);
    Serial.println();
  }
}