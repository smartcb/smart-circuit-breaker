#include <PZEM004Tv30.h>

class PZEMModule {
private:
    PZEM004Tv30 pzem;

public:
    PZEMModule(HardwareSerial& serial, int rxPin, int txPin) : pzem(serial, rxPin, txPin) {}

    float getVoltage() { return pzem.voltage(); }
    float getCurrent() { return pzem.current(); }
    float getPower()   { return pzem.power(); }
    float getEnergy()  { return pzem.energy(); }
};
