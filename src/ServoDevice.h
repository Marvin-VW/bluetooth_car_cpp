#ifndef SERVODEVICE_H
#define SERVODEVICE_H

#include <Arduino.h>
#include "Device.h"

class ServoDevice : public Device {
  private:
    int ledPin;
    int ledChannel;
    int frequency;
    int resolution;
    int angle;

  public:
    ServoDevice(int pin, int channel = 1, int freq = 50, int res = 16) 
      : ledPin(pin), ledChannel(channel), frequency(freq), resolution(res), angle(0) {}

    void setup() override {
        ledcSetup(ledChannel, frequency, resolution);
        ledcAttachPin(ledPin, ledChannel);
    }

    void setAngle(int a) {
        //Pulse Cycle: ca. 20 ms
        float bottom = std::pow(2,resolution) / 40; //Pulse Width: 500 μs
        float top = std::pow(2,resolution) / 8.3; //Pulse Width: 2400 μs
        int dutyCycle = map(a, 0, 180, static_cast<int>(bottom), static_cast<int>(top));
        ledcWrite(ledChannel, dutyCycle);
    }

    void action() override {
        setAngle(angle);
    }
};

#endif
