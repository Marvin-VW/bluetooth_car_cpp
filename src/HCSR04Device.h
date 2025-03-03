#ifndef HCSR04DEVICE_H
#define HCSR04DEVICE_H

#include <Arduino.h>
#include "Device.h"

class HCSR04Device : public Device {
  private:
    int triggerPin;
    int echoPin;
    float temperature;  // Temperature in Celsius

  public:
    HCSR04Device(int trig, int echo) : triggerPin(trig), echoPin(echo), temperature(20.0) {} // Default temperature is 20°C

    void setup() override {
        pinMode(triggerPin, OUTPUT);
        pinMode(echoPin, INPUT);
    }

    // Method to set the temperature
    void setTemperature(float temp) {
        temperature = temp;
    }

    long measureDistance() {
        // Calculate speed of sound based on temperature
        //Serial.println(temperature);
        float speedOfSound = 331.3 + (0.606 * temperature);

        // Trigger pulse
        digitalWrite(triggerPin, LOW);
        delayMicroseconds(2);
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);

        long duration = pulseIn(echoPin, HIGH);

        // Calculate distance based on speed of sound
        long distance = (duration * speedOfSound) / 2 / 10000; // Convert to cm
        return distance;
    }

    void action() override {
        measureDistance();
    }
};

#endif
