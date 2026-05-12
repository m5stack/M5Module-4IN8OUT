#include "MODULE_4IN8OUT.h"

bool MODULE_4IN8OUT::begin(m5::I2C_Class* i2c, uint8_t addr, uint32_t freq) {
    _i2c  = i2c;
    _addr = addr;
    _freq = freq;
    return _i2c->scanID(_addr, _freq);
}

bool MODULE_4IN8OUT::writeBytes(uint8_t reg, uint8_t* buffer, uint8_t length) {
    return _i2c->writeRegister(_addr, reg, buffer, length, _freq);
}

bool MODULE_4IN8OUT::readBytes(uint8_t reg, uint8_t* buffer, uint8_t length) {
    return _i2c->readRegister(_addr, reg, buffer, length, _freq);
}

bool MODULE_4IN8OUT::getInput(uint8_t index) {
    uint8_t data = 0;
    if (readBytes(MODULE_4IN8OUT_INPUT_REG + index, &data, 1)) {
        return data ? true : false;
    }
    return false;
}

bool MODULE_4IN8OUT::setOutput(uint8_t index, bool state) {
    uint8_t data = state ? 0x01 : 0x00;
    return writeBytes(MODULE_4IN8OUT_OUTPUT_REG + index, &data, 1);
}

bool MODULE_4IN8OUT::setAllOutput(bool state) {
    uint8_t data[2] = {0};
    if (state) {
        memset(data, 0xff, 2);
    }
    return writeBytes(MODULE_4IN8OUT_OUTPUT_REG, data, 2);
}

bool MODULE_4IN8OUT::reverseOutput() {
    uint8_t data[2] = {0};
    if (readBytes(MODULE_4IN8OUT_OUTPUT_REG, data, 2)) {
        for (uint8_t i = 0; i < 2; i++) {
            data[i] = ~data[i];
        }
        return writeBytes(MODULE_4IN8OUT_OUTPUT_REG, data, 2);
    }
    return false;
}

uint8_t MODULE_4IN8OUT::getVersion() {
    uint8_t data = 0;
    readBytes(MODULE_4IN8OUT_VERSION_REG, &data, 1);
    return data;
}

bool MODULE_4IN8OUT::setDeviceAddr(uint8_t addr) {
    uint8_t data = addr;
    if (writeBytes(MODULE_4IN8OUT_ADDR_CONFIG_REG, &data, 1)) {
        _addr = addr;
        return true;
    }
    return false;
}
