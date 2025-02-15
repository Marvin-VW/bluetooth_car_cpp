#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Wire.h>

#include "ServoDevice.h"
#include "LEDDevice.h"
#include "MotorDevice.h"
#include "HCSR04Device.h"
#include "INA3221.h"

#define INA3221_ADDRESS 0x40 // Default I2C address

ServoDevice Servo(13);
LEDDevice Underglow(12);
MotorDevice Motor(27, 26, 25);
HCSR04Device Sensor_Left(17, 16);
HCSR04Device Sensor_Right(19, 18);

INA3221 Voltage_Sensor(INA3221_ADDRESS);

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
    Voltage_Sensor.begin(2,15);


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
        else if (msg.startsWith("Left Joystick:")) {
            msg.remove(0, 15);
        }
        else if (msg.startsWith("Right Joystick:")) {
            msg.remove(0, 16);
        }

    }

    // Timed Sending
    if (currentMillis - previousMillis >= sendInterval) {
        previousMillis = currentMillis;
        
        long distance_left = Sensor_Left.measureDistance();
        long distance_right = Sensor_Right.measureDistance();
        float busVoltage = Voltage_Sensor.getBusVoltage();
        float shuntVoltage = Voltage_Sensor.getShuntVoltage();
        float current = Voltage_Sensor.getCurrent(0.1); // 100mΩ (0.1Ω) shunt resistor


        SerialBT.print(String(distance_left) + "," + String(distance_right) + "," + "100" 
            + "," + String(busVoltage) + "," + String(shuntVoltage * 1000) + "," + String(current));

    }

    delay(20);
}
