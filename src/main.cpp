#include <Arduino.h>
#include <TFT_eSPI.h>
#include "PZEMModule.h"
#include "TFTDisplay.h"

// Initialize TFT display and PZEM modules
TFT_eSPI tft = TFT_eSPI();
TFTDisplay display(tft);

HardwareSerial PZEMSerial1(1);  // UART1
HardwareSerial PZEMSerial2(2);  // UART2
HardwareSerial PZEMSerial3(3);  // UART3

PZEMModule pzem1(PZEMSerial1, 16, 17); // RX1, TX1
PZEMModule pzem2(PZEMSerial2, 18, 19); // RX2, TX2
PZEMModule pzem3(PZEMSerial3, 21, 22); // RX3, TX3

void setup() {
    Serial.begin(115200);
    display.initialize();
}

void loop() {
    // Get readings from each PZEM module
    // float voltage1 = pzem1.getVoltage();
    // float current1 = pzem1.getCurrent();
    // float power1 = pzem1.getPower();
    // float energy1 = pzem1.getEnergy();

    float voltage1 = 220;
    float current1 = 0.1;
    float power1 = 1.2;
    float energy1 = 1.5;

    float voltage2 = pzem2.getVoltage();
    float current2 = pzem2.getCurrent();
    float power2 = pzem2.getPower();
    float energy2 = pzem2.getEnergy();

    float voltage3 = pzem3.getVoltage();
    float current3 = pzem3.getCurrent();
    float power3 = pzem3.getPower();
    float energy3 = pzem3.getEnergy();

    // Display values in each section of the TFT display
    display.displayValues(0, voltage1, current1, power1, energy1);
    display.displayValues(1, voltage2, current2, power2, energy2);
    display.displayValues(2, voltage3, current3, power3, energy3);

    delay(1000);  // Update every second
}
