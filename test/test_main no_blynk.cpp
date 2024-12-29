/* Fill-in information from Blynk Device Info here */
// OLD BLYNK TOKEN
// #define BLYNK_TEMPLATE_ID "TMPL6cHiIx4SW"
// #define BLYNK_TEMPLATE_NAME "Smart Circuit Breaker"
// #define BLYNK_AUTH_TOKEN "3Yv_0pOJia2C7i-bt-2XM09BRMeaPFE7"

// NEW BLYNK TOKEN
#define BLYNK_TEMPLATE_ID "TMPL6-3UKmQjI"
#define BLYNK_TEMPLATE_NAME "Smart Circuit Breaker"
#define BLYNK_AUTH_TOKEN "iFYO5QYTCHszBXZQI3NabYkLcP4VmO0D"


/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <ArduinoJson.h>
#include <MycilaPZEM004Tv3.h>
#include <TFT_eSPI.h>
#include "constants.h" // Include constants file
#include "TFTDisplay.h"
#include <elapsedMillis.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "donskytech-1stFloor";
char pass[] = "donsky982";

BlynkTimer timer;

Mycila::PZEM pzem1;
Mycila::PZEM pzem2;
Mycila::PZEM pzem3;

// TFTDisplay instance
TFT_eSPI tft = TFT_eSPI();
TFTDisplay display(tft);

// Variables for elapsed time tracking
elapsedMillis totalElapsed;                // Tracks total cycle time
elapsedMillis moduleElapsed;               // Tracks time between module readings
const unsigned long totalInterval = 5000;  // 5 seconds for a complete cycle
const unsigned long moduleInterval = 1000; // 1 second between module readings
int currentModule = 0;                     // Tracks which PZEM module to read

void sendReadings(JsonDocument doc);

#define SSR1_CONTROL_PIN 32 // GPIO pin to control SSR 1 
#define SSR2_CONTROL_PIN 33 // GPIO pin to control SSR 2 
#define SSR3_CONTROL_PIN 25 // GPIO pin to control SSR 3 

// // This function is called every time the Virtual Pin 6 state changes
// BLYNK_WRITE(V6)
// {
//   // Set incoming value from pin V0 to a variable
//   int value = param.asInt();

//   // Control the LED based on V0's value
//   if (value == 1)
//   {
//     digitalWrite(SSR1_CONTROL_PIN, HIGH);
//   }
//   else
//   {
//     digitalWrite(SSR1_CONTROL_PIN, LOW);
//   }
// }

// // This function is called every time the Virtual Pin 6 state changes
// BLYNK_WRITE(V7)
// {
//   // Set incoming value from pin V0 to a variable
//   int value = param.asInt();

//   // Control the LED based on V0's value
//   if (value == 1)
//   {
//     digitalWrite(SSR2_CONTROL_PIN, HIGH);
//   }
//   else
//   {
//     digitalWrite(SSR2_CONTROL_PIN, LOW);
//   }
// }

// // This function is called every time the Virtual Pin 6 state changes
// BLYNK_WRITE(V8)
// {
//   // Set incoming value from pin V0 to a variable
//   int value = param.asInt();

//   // Control the LED based on V0's value
//   if (value == 1)
//   {
//     digitalWrite(SSR3_CONTROL_PIN, HIGH);
//   }
//   else
//   {
//     digitalWrite(SSR3_CONTROL_PIN, LOW);
//   }
// }



void setup()
{
  Serial.begin(115200);
  while (!Serial)
    continue;

  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(SSR1_CONTROL_PIN, OUTPUT); // Set pin as output
  pinMode(SSR2_CONTROL_PIN, OUTPUT); // Set pin as output
  pinMode(SSR3_CONTROL_PIN, OUTPUT); // Set pin as output

  // Initialize TFT display
  display.initialize();

  // Initialize PZEM modules
  pzem1.begin(Serial1, 14, 27, 0x01, true);
  pzem2.begin(Serial1, 14, 27, 0x02, true);
  pzem3.begin(Serial1, 14, 27, 0x03, true);

  // Set all SSR to OFF during boot
  digitalWrite(SSR1_CONTROL_PIN, LOW);
  digitalWrite(SSR2_CONTROL_PIN, LOW);
  digitalWrite(SSR3_CONTROL_PIN, LOW);
}

void loop()
{
  // Reset the cycle if the total elapsed time exceeds the total interval
  if (totalElapsed >= totalInterval)
  {
    totalElapsed = 0;  // Reset the total cycle timer
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
        // sendReadings(doc);
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
        // sendReadings(doc);
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
        // sendReadings(doc);
      }
      break;
    }

    // Move to the next module
    currentModule++;
  }
  Blynk.run();
}

void sendReadings(JsonDocument doc)
{
  // Check if keys exist and retrieve their values
  float voltage = doc["voltage"].is<float>() ? doc["voltage"].as<float>() : 0.0;
  float current = doc["current"].is<float>() ? doc["current"].as<float>() : 0.0;

  if (voltage == 0.0)
  {
    if (currentModule == 0)
    {
      Blynk.logEvent("voltage_cut_line_1", "Line 1 is cut!");
    }
    else if (currentModule == 1)
    {
      Blynk.logEvent("voltage_cut_line_2", "Line 2 is cut!");
    }
    else if (currentModule == 1)
    {
      Blynk.logEvent("voltage_cut_line_3", "Line 3 is cut!");
    }
  }

  // Send voltage
  if (currentModule == 0)
  {
    Blynk.virtualWrite(V0, voltage);
    Blynk.virtualWrite(V1, current);
  }
  else if (currentModule == 1)
  {
    Blynk.virtualWrite(V2, voltage);
    Blynk.virtualWrite(V3, current);
  }
  else if (currentModule == 2)
  {
    Blynk.virtualWrite(V4, voltage);
    Blynk.virtualWrite(V5, current);
  }
}
