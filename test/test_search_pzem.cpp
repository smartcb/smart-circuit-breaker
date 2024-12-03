/*
 * This example shows how to search for PZEM004Tv3 devices on the same Serial port.
 * PZEM have to be assigned addresses before using this example.
 *
 * The circuit:
 * - PZEM004Tv3 #1 connected to Serial1 (RX=14, TX=27)
 * - PZEM004Tv3 #2 connected to Serial1 (RX=14, TX=27)
 */
#include <Arduino.h>
#include <MycilaPZEM004Tv3.h>

Mycila::PZEM pzem1;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    continue;

  pzem1.begin(Serial1, 14, 27);

  uint8_t addresses[255];
  size_t count = pzem1.search(addresses, 255);

  Serial.printf("Found %d devices\n", count);
  for (size_t i = 0; i < count; i++) {
    Serial.printf("Address: 0x%02X\n", addresses[i]);
  }

  pzem1.end();
}

void loop() {
  vTaskDelete(NULL);
}