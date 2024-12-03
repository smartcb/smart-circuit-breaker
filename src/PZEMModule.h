// SPDX-License-Identifier: MIT
/*
 * Copyright (C) 2023-2024 Mathieu Carbou
 */
#pragma once

#include "MycilaPZEM004Tv3.h"

namespace Mycila {
  class PZEMModule : public PZEM {
  public:
    PZEMModule(HardwareSerial& serial, int8_t rxPin, int8_t txPin, uint8_t address = MYCILA_PZEM_ADDRESS_GENERAL)
        : _serial(serial), _rxPin(rxPin), _txPin(txPin), _address(address) {}

    void init(bool async = false) {
      begin(_serial, _rxPin, _txPin, _address, async);
    }

    void reset() {
      end();
      _serial.end();
    }

    bool fetchData() {
      return read(); // Calls the base class `PZEM::read()`
    }

    float getVoltage() const { return data.voltage; }
    float getCurrent() const { return data.current; }
    float getPower() const { return data.activePower; }
    float getEnergy() const { return data.activeEnergy; }

  private:
    HardwareSerial& _serial;
    int8_t _rxPin;
    int8_t _txPin;
    uint8_t _address;
  };
}
