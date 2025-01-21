#ifndef LED_H
#define LED_H

void initializeLed(int pin); // Initialisiert eine LED und setzt den Pin als OUTPUT.
void turnOnLed(int pin); // Schaltet die LED ein.
void turnOffLed(int pin); // Schaltet die LED aus.
void toggleLed(int pin); // Schaltet den aktuellen Zustand der LED um.
void blinkLed(int pin, int duration); // Lässt die LED für eine bestimmte Dauer blinken.
void fadeLed(int pin, int startBrightness, int endBrightness, int duration); // Simuliert das Faden der LED.
bool isLedOn(int pin); // Gibt den aktuellen Zustand der LED zurück.

#endif // LED_H
