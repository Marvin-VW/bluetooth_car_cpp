#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Wire.h>

#include "ServoDevice.h"
#include "LEDDevice.h"
#include "MotorDevice.h"
#include "HCSR04Device.h"
#include "INA3221.h"

#define INA3221_ADDRESS 0x40

ServoDevice Servo(13);
LEDDevice Underglow(12);
MotorDevice Motor(27, 26, 25);
HCSR04Device Sensor_Left(17, 16);
HCSR04Device Sensor_Right(19, 18);
INA3221 Voltage_Sensor(INA3221_ADDRESS, &Wire);

BluetoothSerial SerialBT;

void receiveBluetoothTask(void *parameter);
void sendSensorDataTask(void *parameter);

void setup() {
    Serial.begin(9600);
    Servo.setup();
    Underglow.setup();
    Motor.setup();
    Sensor_Left.setup();
    Sensor_Right.setup();

    Wire.begin(2, 15);
    Voltage_Sensor.begin();

    SerialBT.begin("Nissan");
    Serial.println("The device started, now you can pair it with Bluetooth!");

    // Create FreeRTOS tasks for Bluetooth communication
    xTaskCreatePinnedToCore(receiveBluetoothTask, "ReceiveBluetooth", 4096, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(sendSensorDataTask, "SendSensorData", 4096, NULL, 1, NULL, 1);
}

void loop() {
    // Empty because tasks handle execution
}

// Task for receiving Bluetooth commands
void receiveBluetoothTask(void *parameter) {
    while (true) {
        String msg = "";
        while (SerialBT.available()) {
            char ch = SerialBT.read();
            msg += ch;
        }

        if (msg != "") {
            msg.replace("\n", "");
            msg.replace("\r", "");

            Serial.println(msg);
            if (msg == "underglow on") {
                Serial.println("Turning on");
                Underglow.turnOn();
            } else if (msg == "underglow off") {
                Serial.println("Turning off");
                Underglow.turnOff();
            } if (msg.startsWith("Left Joystick")) {
                int colonPos = msg.indexOf(':');
                if (colonPos != -1) {
                    String valueStr = msg.substring(colonPos + 1);
                    valueStr.trim();
                    double value = valueStr.toDouble();
                    int result = static_cast<int>(value * -100);
                    Motor.setSpeed(result);
                    Serial.print(result);
                }
            }
            if (msg.startsWith("Right Joystick")) {
                int colonPos = msg.indexOf(':');
                if (colonPos != -1) {
                    String valueStr = msg.substring(colonPos + 1);  // Extract the number part
                    valueStr.trim();  // Remove any extra spaces
                    double value = valueStr.toDouble();  // Convert to double
                }
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS); // Small delay to prevent task hogging
    }
}

// Task for sending sensor data over Bluetooth
void sendSensorDataTask(void *parameter) {
    const unsigned long sendInterval = 1000;
    unsigned long previousMillis = millis();

    while (true) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= sendInterval) {
            previousMillis = currentMillis;

            long distance_left = Sensor_Left.measureDistance();
            long distance_right = Sensor_Right.measureDistance();

            float busVoltage = Voltage_Sensor.getBusVoltage(2);
            float shuntVoltage = Voltage_Sensor.getShuntVoltage_mV(2);
            float current = Voltage_Sensor.getCurrent_mA(2) / 1000;

            String data = String(distance_left) + "," + String(distance_right) + ",100," + 
                          String(busVoltage) + "," + String(shuntVoltage) + "," + String(current);
            
            SerialBT.println(data);
        }

        vTaskDelay(50 / portTICK_PERIOD_MS); // Prevent CPU overload
    }
}
