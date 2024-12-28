#include <Arduino.h>

#define SSR_CONTROL_PIN_1 32 // GPIO pin to control the transistor
#define SSR_CONTROL_PIN_2 33 // GPIO pin to control the transistor
#define SSR_CONTROL_PIN_3 25 // GPIO pin to control the transistor

void setup()
{
    pinMode(SSR_CONTROL_PIN_1, OUTPUT); // Set pin as output
    pinMode(SSR_CONTROL_PIN_2, OUTPUT); // Set pin as output
    pinMode(SSR_CONTROL_PIN_3, OUTPUT); // Set pin as output
    digitalWrite(SSR_CONTROL_PIN_1, LOW);
    digitalWrite(SSR_CONTROL_PIN_2, LOW);
    digitalWrite(SSR_CONTROL_PIN_3, LOW);
}

void loop()
{ // Turn on LED
    digitalWrite(SSR_CONTROL_PIN_1, HIGH);
    delay(1000); // LED on for 1 second

    // Turn off LED
    digitalWrite(SSR_CONTROL_PIN_2, LOW);
    delay(1000); // LED off for 1 second

    // Turn on LED
    digitalWrite(SSR_CONTROL_PIN_2, HIGH);
    delay(1000); // LED on for 1 second

    // Turn off LED
    digitalWrite(SSR_CONTROL_PIN_2, LOW);
    delay(1000); // LED off for 1 second

    // Turn on LED
    digitalWrite(SSR_CONTROL_PIN_3, HIGH);
    delay(1000); // LED on for 1 second

    // Turn off LED
    digitalWrite(SSR_CONTROL_PIN_3, LOW);
    delay(1000); // LED off for 1 second
}
