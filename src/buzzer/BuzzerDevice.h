#ifndef BUZZERDEVICE_H
#define BUZZERDEVICE_H

#include "Arduino.h"

class BuzzerDevice {
private:
    int pin;

public:
    BuzzerDevice(int buzzerPin) : pin(buzzerPin) {}

    void setup() {
        pinMode(pin, OUTPUT);
    }

    void playContinuousTone() {
        tone(pin, 40);
    }

    void playBeep() {
        tone(pin, 60);
        delay(400),
        noTone(pin),
        delay(400);
    }

    void stopTone() {
        noTone(pin);
    }
};

#endif // BUZZERDEVICE_H
