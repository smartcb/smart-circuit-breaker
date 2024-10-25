#include <PZEM004Tv30.h>  // Include the library for PZEM-004T v3.0

// Define RX and TX pins for ESP32 hardware serial communication
#define PZEM_RX_PIN 16   // Connect this to the TX pin of PZEM
#define PZEM_TX_PIN 17   // Connect this to the RX pin of PZEM

// Create PZEM object
HardwareSerial PZEMSerial(1);  // Use UART1 on ESP32
PZEM004Tv30 pzem(PZEMSerial, PZEM_RX_PIN, PZEM_TX_PIN);  // Use the correct constructor for ESP32

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Start serial communication with PZEM-004T via HardwareSerial (pins 16, 17)
  PZEMSerial.begin(9600, SERIAL_8N1, PZEM_RX_PIN, PZEM_TX_PIN);
  
  Serial.println("PZEM-004T Meter Reading:");
}

void loop() {
  float voltage = pzem.voltage();   // Read voltage
  float current = pzem.current();   // Read current
  float power = pzem.power();       // Read active power
  float energy = pzem.energy();     // Read total energy

  // Check if readings are valid (not NaN)
  if(!isnan(voltage)) {
    Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
  } else {
    Serial.println("Error reading voltage");
  }

  if(!isnan(current)) {
    Serial.print("Current: "); Serial.print(current); Serial.println(" A");
  } else {
    Serial.println("Error reading current");
  }

  if(!isnan(power)) {
    Serial.print("Power: "); Serial.print(power); Serial.println(" W");
  } else {
    Serial.println("Error reading power");
  }

  if(!isnan(energy)) {
    Serial.print("Energy: "); Serial.print(energy); Serial.println(" Wh");
  } else {
    Serial.println("Error reading energy");
  }

  delay(1000);  // Wait 1 second before reading again
}
