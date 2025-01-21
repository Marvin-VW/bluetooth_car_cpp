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

    void action() override { //toggle
        digitalWrite(pin, state ? HIGH : LOW);
    }

    void blinkLed(int duration) {
        digitalWrite(pin, HIGH);
        delay(duration);
        digitalWrite(pin, LOW);
        delay(duration);
    }

    void fadeLed(int startBrightness, int endBrightness, int duration) {
    int steps = 100;
    int delayTime = duration / steps;
    for (int i = 0; i <= steps; i++) {
        int brightness = map(i, 0, steps, startBrightness, endBrightness);
        analogWrite(pin, brightness);
        delay(delayTime);
    }
}
};

#endif
