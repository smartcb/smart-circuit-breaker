#include <PZEM004Tv30.h>  // Include the library for PZEM-004T v3.0
#include <SoftwareSerial.h>  // Include SoftwareSerial library for ESP32

class PZEMModule {
private:
    PZEM004Tv30* pzem;         // Pointer to PZEM004Tv30 class
    Stream &serial;            // Reference to the Stream object (could be HardwareSerial or SoftwareSerial)

public:
    // Constructor for HardwareSerial
    PZEMModule(HardwareSerial &serialPort, uint8_t rx, uint8_t tx) : serial(serialPort) {
        pzem = new PZEM004Tv30(serialPort, rx, tx);
        serialPort.begin(9600);  // Start serial communication for the module
    }

    // Constructor for SoftwareSerial (for ESP32 or AVR)
    PZEMModule(SoftwareSerial &serialPort, uint8_t addr = PZEM_DEFAULT_ADDR) : serial(serialPort) {
        #if defined(PZEM004_SOFTSERIAL)  // Ensure compatibility with SoftwareSerial if supported
        pzem = new PZEM004Tv30(serialPort, addr);
        serialPort.begin(9600);  // Start serial communication for the module
        #else
        Serial.println("SoftwareSerial not supported on this platform");
        #endif
    }

    // Destructor to clean up dynamic allocation
    ~PZEMModule() {
        delete pzem;
    }

    // Method to get voltage
    float getVoltage() {
        return pzem->voltage();
    }

    // Method to get current
    float getCurrent() {
        return pzem->current();
    }

    // Method to get power
    float getPower() {
        return pzem->power();
    }

    // Method to get energy
    float getEnergy() {
        return pzem->energy();
    }

    // Method to print all readings
    void printReadings() {
        float voltage = getVoltage();
        float current = getCurrent();
        float power = getPower();
        float energy = getEnergy();

        // Check and print the voltage
        if (!isnan(voltage)) {
            Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
        } else {
            Serial.println("Error reading voltage");
        }

        // Check and print the current
        if (!isnan(current)) {
            Serial.print("Current: "); Serial.print(current); Serial.println(" A");
        } else {
            Serial.println("Error reading current");
        }

        // Check and print the power
        if (!isnan(power)) {
            Serial.print("Power: "); Serial.print(power); Serial.println(" W");
        } else {
            Serial.println("Error reading power");
        }

        // Check and print the energy
        if (!isnan(energy)) {
            Serial.print("Energy: "); Serial.print(energy); Serial.println(" Wh");
        } else {
            Serial.println("Error reading energy");
        }
    }
};
