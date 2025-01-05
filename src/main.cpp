#include <Arduino.h>
#include <BluetoothSerial.h>

#include "ServoDevice.h"
#include "LEDDevice.h"
#include "MotorDevice.h"
#include "HCSR04Device.h"

ServoDevice Servo(13);
LEDDevice Underglow(12);
MotorDevice Motor(27, 26, 25);
HCSR04Device Sensor_Left(17, 16);
HCSR04Device Sensor_Right(19, 18);

BluetoothSerial SerialBT;

unsigned long previousMillis = 0;
const unsigned long sensorInterval = 100;
const unsigned long sendInterval = 1000;

void setup() {
    Serial.begin(9600);
    Servo.setup();
    Underglow.setup();
    Motor.setup();
    Sensor_Left.setup();
    Sensor_Right.setup();

    SerialBT.begin("Nissan"); //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
}


void loop() {
    unsigned long currentMillis = millis();

    // Continuous Reading
    String msg = "";
    while (SerialBT.available()) {
        char ch = SerialBT.read();
        msg += ch;
    }
    
    if (msg != "") {
        // Remove all LF (Line Feed)
        int index;
        while ((index = msg.indexOf(10)) != -1) {
            msg.remove(index);
        }

        // Remove all CR (Carriage Return)
        while ((index = msg.indexOf(13)) != -1) {
            msg.remove(index);
        }

        // Process Commands
        Serial.println(msg);
        if (msg == "underglow on") {
            Serial.println("Turning on");
            Underglow.turnOn();
        } else if (msg == "underglow off") {
            Serial.println("Turning off");
            Underglow.turnOff();
        }
    }

    // Timed Sending
    if (currentMillis - previousMillis >= sendInterval) {
        previousMillis = currentMillis;
        
        // Example of sending a message every second
        SerialBT.print("hello");
        //Serial.println("Message sent: hello");

        // long distance_left = Sensor_Left.measureDistance();
        // long distance_right = Sensor_Right.measureDistance();
        // Serial.println("Distances: Left = " + String(distance_left) + ", Right = " + String(distance_right));
    }

    delay(20);
}
