#ifndef INA3221_H
#define INA3221_H

#include <Wire.h>

#define INA3221_REG_CONFIG            0x00
#define INA3221_REG_BUS_VOLTAGE_CH3   0x06
#define INA3221_REG_SHUNT_VOLTAGE_CH3 0x07

class INA3221 {
public:
    INA3221(uint8_t address);
    void begin(int sda, int scl);

    float getBusVoltage();
    float getShuntVoltage();
    float getCurrent(float shunt_resistance);

private:
    uint8_t _address;
    uint16_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint16_t value);
};

#endif
