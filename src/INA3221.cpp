#include "INA3221.h"

INA3221::INA3221(uint8_t address) : _address(address) {}

void INA3221::begin(int sda, int scl) {
    Wire.begin(sda, scl);  // Initialize I2C with specified SDA and SCL

    // Set PGA to 1x (±327.68mV shunt voltage range)
    writeRegister(INA3221_REG_CONFIG, 0x7127);
}

float INA3221::getBusVoltage() {
    uint16_t raw = readRegister(INA3221_REG_BUS_VOLTAGE_CH3);
    return raw * 0.001; // Convert to volts (1.0mV per bit)
}

float INA3221::getShuntVoltage() {
    int16_t raw = (int16_t) readRegister(INA3221_REG_SHUNT_VOLTAGE_CH3); // Signed 16-bit value
    return raw * 0.00004; // Convert to volts (40µV per bit)
}

float INA3221::getCurrent(float shunt_resistance) {
    return getShuntVoltage() / shunt_resistance; // Ohm's Law: I = V/R
}

uint16_t INA3221::readRegister(uint8_t reg) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_address, (uint8_t)2);

    if (Wire.available() == 2) {
        return (Wire.read() << 8) | Wire.read();
    }
    return 0;
}

void INA3221::writeRegister(uint8_t reg, uint16_t value) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write((value >> 8) & 0xFF);  // High byte
    Wire.write(value & 0xFF);         // Low byte
    Wire.endTransmission();
}
