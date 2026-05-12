#ifndef _MODULE_4IN8OUT_H
#define _MODULE_4IN8OUT_H

#include "Arduino.h"
#include <M5Unified.h>

#define MODULE_4IN8OUT_ADDR            0x45
#define MODULE_4IN8OUT_INPUT_REG       0x10
#define MODULE_4IN8OUT_OUTPUT_REG      0x20
#define MODULE_4IN8OUT_VERSION_REG     0xFE
#define MODULE_4IN8OUT_ADDR_CONFIG_REG 0xFF
#define MODULE_4IN8OUT_I2C_FREQ        100000

class MODULE_4IN8OUT {
   private:
    uint8_t _addr;
    m5::I2C_Class* _i2c;
    uint32_t _freq;
    bool writeBytes(uint8_t reg, uint8_t* buffer, uint8_t length);
    bool readBytes(uint8_t reg, uint8_t* buffer, uint8_t length);

   public:
    bool begin(m5::I2C_Class* i2c = &M5.In_I2C,
               uint8_t addr       = MODULE_4IN8OUT_ADDR,
               uint32_t freq      = MODULE_4IN8OUT_I2C_FREQ);
    bool setOutput(uint8_t index, bool state);
    bool setAllOutput(bool state);
    bool reverseOutput();
    bool getInput(uint8_t index);
    bool setDeviceAddr(uint8_t addr);
    uint8_t getVersion();
};

#endif
