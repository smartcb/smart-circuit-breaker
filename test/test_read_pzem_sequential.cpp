#include <Arduino.h>
#include <ArduinoJson.h>
#include <MycilaPZEM004Tv3.h>
#include <TFT_eSPI.h>
#include "constants.h" // Include constants file
#include "TFTDisplay.h"
#include <elapsedMillis.h>

Mycila::PZEM pzem1;
Mycila::PZEM pzem2;
Mycila::PZEM pzem3;

// TFTDisplay instance
TFT_eSPI tft = TFT_eSPI();
TFTDisplay display(tft);

// Variables for elapsed time tracking
elapsedMillis totalElapsed; // Tracks total cycle time
elapsedMillis moduleElapsed; // Tracks time between module readings
const unsigned long totalInterval = 5000; // 5 seconds for a complete cycle
const unsigned long moduleInterval = 1000; // 1 second between module readings
int currentModule = 0; // Tracks which PZEM module to read

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    continue;

  // Initialize TFT display
  display.initialize();

  // Initialize PZEM modules
  pzem1.begin(Serial1, 14, 27, 0x01, true);
  pzem2.begin(Serial1, 14, 27, 0x02, true);
  pzem3.begin(Serial1, 14, 27, 0x03, true);
}

void loop()
{
  // Reset the cycle if the total elapsed time exceeds the total interval
  if (totalElapsed >= totalInterval)
  {
    totalElapsed = 0; // Reset the total cycle timer
    currentModule = 0; // Restart from the first module
  }

  // Check if it's time to read the next module
  if (moduleElapsed >= moduleInterval && currentModule < 3)
  {
    moduleElapsed = 0; // Reset the module timer

    JsonDocument doc;
    switch (currentModule)
    {
    case 0: // Read PZEM1
      if (pzem1.isEnabled())
      {
        pzem1.toJson(doc.to<JsonObject>());
        Serial.printf("0x%02X ", pzem1.getDeviceAddress());
        serializeJson(doc, Serial);
        Serial.println();
        display.displayValues(0, doc); // Display in section 0
      }
      break;

    case 1: // Read PZEM2
      if (pzem2.isEnabled())
      {
        pzem2.toJson(doc.to<JsonObject>());
        Serial.printf("0x%02X ", pzem2.getDeviceAddress());
        serializeJson(doc, Serial);
        Serial.println();
        display.displayValues(1, doc); // Display in section 1
      }
      break;

    case 2: // Read PZEM3
      if (pzem3.isEnabled())
      {
        pzem3.toJson(doc.to<JsonObject>());
        Serial.printf("0x%02X ", pzem3.getDeviceAddress());
        serializeJson(doc, Serial);
        Serial.println();
        display.displayValues(2, doc); // Display in section 2
      }
      break;
    }

    // Move to the next module
    currentModule++;
  }
}
