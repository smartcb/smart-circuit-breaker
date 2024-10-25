#include <Arduino.h>
#include <TFT_eSPI.h> 
TFT_eSPI tft = TFT_eSPI();


void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize TFT display
  tft.init();
  tft.setRotation(1);        // Set rotation to landscape mode
  tft.fillScreen(TFT_BLACK); // Clear the screen
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color

  // Draw two vertical lines to divide the screen into three sections
  tft.drawLine(160, 0, 160, 480, TFT_WHITE);  // First dividing line at x = 106
  tft.drawLine(320, 0, 320, 480, TFT_WHITE);  // Second dividing line at x = 213

  Serial.println("PZEM-004T Meter Readings on TFT:");
}



void loop() 
{
  // put your main code here, to run repeatedly:
}