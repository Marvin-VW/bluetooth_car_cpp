#ifndef MOTORDEVICE_H
#define MOTORDEVICE_H

#include <Arduino.h>
#include "Device.h"

class MotorDevice : public Device {
  private:
    int enablePin;   // ENA pin for PWM control
    int in1Pin;      // IN1 pin for direction
    int in2Pin;      // IN2 pin for direction
    int speed;       // Motor speed (0 to 255)

  public:
    MotorDevice(int ena, int in1, int in2) 
      : enablePin(ena), in1Pin(in1), in2Pin(in2), speed(0) {}

    void setup() override {
        // Set pins to output mode
        pinMode(enablePin, OUTPUT);
        pinMode(in1Pin, OUTPUT);
        pinMode(in2Pin, OUTPUT);
        stop(); // Initialize with motor stopped
    }

    void setSpeed(int s) {
        speed = map(abs(s), 0, 100, 0, 255); // Limit speed to valid range (0-255)

        if (s > 0) {
            // Set direction to forward
            digitalWrite(in1Pin, HIGH);
            digitalWrite(in2Pin, LOW);
        } else if (s < 0) {
            // Set direction to reverse
            digitalWrite(in1Pin, LOW);
            digitalWrite(in2Pin, HIGH);
        } else {
            stop();
        }

        analogWrite(enablePin, speed);
    }

    void stop() {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);
        analogWrite(enablePin, 0); // Set enable pin to 0 to stop the motor
    }

    void action() override {
        analogWrite(enablePin, speed);
    }
};

#endif
