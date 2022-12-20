#ifndef _MODULE_4IN8OUT_H
#define _MODULE_4IN8OUT_H

#include "Arduino.h"
#include "Wire.h"

#define MODULE_4IN8OUT_ADDR            0x45
#define MODULE_4IN8OUT_INPUT_REG       0x10
#define MODULE_4IN8OUT_OUTPUT_REG      0x20
#define MODULE_4IN8OUT_VERSION_REG     0xFE
#define MODULE_4IN8OUT_ADDR_CONFIG_REG 0xFF

class MODULE_4IN8OUT {
   private:
    uint8_t _addr;
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    bool writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    bool readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

   public:
    bool begin(TwoWire* wire = &Wire, uint8_t sda = 21, uint8_t scl = 22,
               uint8_t addr = MODULE_4IN8OUT_ADDR);
    bool setOutput(uint8_t index, bool state);
    bool setAllOutput(bool state);
    bool reverseOutput();
    bool getInput(uint8_t index);
    bool setDeviceAddr(uint8_t addr);
    uint8_t getVersion();
};

#endif
