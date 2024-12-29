#include <Arduino.h>

#define LED_CONTROL_PIN 32  // GPIO pin to control the transistor

void setup() {
  pinMode(LED_CONTROL_PIN, OUTPUT); // Set pin as output
}

void loop() {
  // Turn on LED
  digitalWrite(LED_CONTROL_PIN, HIGH);
  delay(5000);  // LED on for 1 second

  // Turn off LED
  digitalWrite(LED_CONTROL_PIN, LOW);
  delay(5000);  // LED off for 1 second
}
