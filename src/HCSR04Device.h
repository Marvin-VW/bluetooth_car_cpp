#ifndef HCSR04DEVICE_H
#define HCSR04DEVICE_H

#include <Arduino.h>
#include "Device.h"

class HCSR04Device : public Device {
  private:
    int triggerPin;
    int echoPin;

  public:
    HCSR04Device(int trig, int echo) : triggerPin(trig), echoPin(echo) {}

    void setup() override {
        pinMode(triggerPin, OUTPUT);
        pinMode(echoPin, INPUT);
    }

    long measureDistance() {
        digitalWrite(triggerPin, LOW);
        delayMicroseconds(2);
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);

        long duration = pulseIn(echoPin, HIGH);
        long distance = duration * 0.034 / 2; // Convert to cm
        return distance;
    }

    void action() override {
        measureDistance();
    }
};

#endif
