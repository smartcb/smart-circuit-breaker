// constants.h

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <TFT_eSPI.h>

// Screen dimensions
const int screenWidth = 480;
const int screenHeight = 320;
const int sectionWidth = screenWidth / 3;

// Text color settings
const uint16_t HEADER_COLOR = TFT_GREEN;
const uint16_t LABEL_COLOR = TFT_GREEN;
const uint16_t VALUE_COLOR = TFT_RED;

// Font sizes
const uint8_t HEADER_FONT = 4;
const uint8_t LABEL_FONT = 2;
const uint8_t VALUE_FONT = 4;

#endif // CONSTANTS_H
