#include <TFT_eSPI.h>
#include "constants.h" // Include constants file
#include <cmath>

class TFTDisplay
{
private:
    TFT_eSPI &tft;
    int screenWidth;
    int screenHeight;
    int sectionWidth;

public:
    TFTDisplay(TFT_eSPI &display) : tft(display), screenWidth(480), screenHeight(320)
    {
        sectionWidth = (screenWidth / 3) - 20;
    }

    void initialize()
    {
        tft.init();
        tft.setRotation(1);          // Set to landscape mode
        tft.fillScreen(TFT_BLACK);   // Clear the screen
        tft.setTextColor(TFT_WHITE); // Set default text color

        // // Optional: Draw test boundaries to ensure coordinates are correct
        tft.drawRect(0, 0, screenWidth, screenHeight, TFT_WHITE); // Red border around the whole screen
    }

    void displayValues(int section, JsonDocument doc)
    {
        float voltage = doc["voltage"] | NAN; // Default to NAN if not present
        float current = doc["current"] | NAN;
        float power = doc["active_power"] | NAN;
        float energy = doc["active_energy"] | NAN;

        int x = section * sectionWidth + 10;
        int y = 20;

        // Clear section before updating
        tft.fillRect(x, 10, sectionWidth - 20, screenHeight - 20, TFT_BLACK);

        // Display PZEM module header
        tft.setTextColor(HEADER_COLOR, TFT_BLACK);
        tft.setTextFont(HEADER_FONT);
        tft.setCursor(x + 40, y);
        tft.printf("LINE %d", section + 1);

        y += 40; // Move down for next line

        // Display Voltage
        tft.setTextFont(LABEL_FONT);   // Label font
        tft.setTextColor(LABEL_COLOR); // Label color
        tft.setCursor(x + 40, y);
        tft.print("Voltage:");

        tft.setTextFont(VALUE_FONT);   // Value font
        tft.setTextColor(VALUE_COLOR); // Value color
        tft.setCursor(x + 40, y + 20);
        tft.printf("%s V", std::isnan(voltage) ? "N/A" : String(voltage, 2).c_str());

        y += 60; // Move down for next reading

        // Display Current
        tft.setTextFont(LABEL_FONT);
        tft.setTextColor(LABEL_COLOR);
        tft.setCursor(x + 40, y);
        tft.print("Current:");

        tft.setTextFont(VALUE_FONT);
        tft.setTextColor(VALUE_COLOR);
        tft.setCursor(x + 40, y + 20);
        tft.printf("%s A", std::isnan(current) ? "N/A" : String(current, 2).c_str());

        y += 60; // Move down for next reading

        // Display Power
        tft.setTextFont(LABEL_FONT);
        tft.setTextColor(LABEL_COLOR);
        tft.setCursor(x + 40, y);
        tft.print("Power:");

        tft.setTextFont(VALUE_FONT);
        tft.setTextColor(VALUE_COLOR);
        tft.setCursor(x + 40, y + 20);
        tft.printf("%s W", std::isnan(power) ? "N/A" : String(power, 2).c_str());

        y += 60; // Move down for next reading

        // Display Energy
        tft.setTextFont(LABEL_FONT);
        tft.setTextColor(LABEL_COLOR);
        tft.setCursor(x + 40, y);
        tft.print("Energy:");

        tft.setTextFont(VALUE_FONT);
        tft.setTextColor(VALUE_COLOR);
        tft.setCursor(x + 40, y + 20);
        tft.printf("%s Wh", std::isnan(energy) ? "N/A" : String(energy, 2).c_str());
    }
};
