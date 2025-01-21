#include "led.h"
#include <Arduino.h>

void initializeLed(int pin) {
    pinMode(pin, OUTPUT); 
}

void turnOnLed(int pin) {
    digitalWrite(pin, HIGH);
}

void turnOffLed(int pin) {
    digitalWrite(pin, LOW);
}

void toggleLed(int pin) {
    int currentState = digitalRead(pin);
    if (currentState == HIGH) {
        digitalWrite(pin, LOW);
    } else {
        digitalWrite(pin, HIGH);
    }
}

void blinkLed(int pin, int duration) {
    turnOnLed(pin);
    delay(duration);
    turnOffLed(pin);
    delay(duration);
}

void fadeLed(int pin, int startBrightness, int endBrightness, int duration) {
    int steps = 100;
    int delayTime = duration / steps;
    for (int i = 0; i <= steps; i++) {
        int brightness = map(i, 0, steps, startBrightness, endBrightness);
        analogWrite(pin, brightness);
        delay(delayTime);
    }
}

bool isLedOn(int pin) {
    return digitalRead(pin) == HIGH;
}
