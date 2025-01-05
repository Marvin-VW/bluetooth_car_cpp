#ifndef LEDDEVICE_H
#define LEDDEVICE_H

#include <Arduino.h>
#include "Device.h"

class LEDDevice : public Device {
  private:
    int pin;
    bool state;

  public:
    LEDDevice(int p) : pin(p), state(false) {}

    void setup() override {
        pinMode(pin, OUTPUT);
    }

    void turnOn() {
        state = true;
        digitalWrite(pin, HIGH);
    }

    void turnOff() {
        state = false;
        digitalWrite(pin, LOW);
    }

    void action() override {
        digitalWrite(pin, state ? HIGH : LOW); // Set based on current state
    }
};

#endif
