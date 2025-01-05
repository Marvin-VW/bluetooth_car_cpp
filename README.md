# Bluetooth Car C++ Code

This project allows you to control a car connected to an ESP32 board via Bluetooth. The devices include a steering servo, LED underglow, motor, and distance sensors. The system uses Bluetooth to receive commands and send sensor data at regular intervals.

## Hardware Requirements

- **ESP32 with Bluetooth**
- **Servo (MG90S)**
- **LEDs**
- **Motor driver (L298N)**
- **Ultrasonic Distance Sensors (HCSR04)**

## Libraries Required

- `BluetoothSerial` - To enable Bluetooth communication between the ESP32 and a mobile device.
- `ServoDevice` - A custom class to control the servo motor.
- `LEDDevice` - A custom class to control LEDs.
- `MotorDevice` - A custom class to control the motor.
- `HCSR04Device` - A custom class to control the HCSR04 ultrasonic distance sensors.

## Pin Configuration

- **Servo Motor**: Pin 13
- **LED UnderGlow**: Pin 12
- **Motor Driver**:
  - Pin 27 (Motor Control)
  - Pin 26 (Motor Control)
  - Pin 25 (Motor Control)
- **HCSR04 Sensors**:
  - Left Sensor: Trigger Pin 17, Echo Pin 16
  - Right Sensor: Trigger Pin 19, Echo Pin 18

## Bluetooth Setup

- The mobile device should be paired with the device named **"Nissan"**.
- The ESP32 communicates with the mobile device using BluetoothSerial, allowing commands to control the devices connected to the ESP32.

## Code Workflow

1. **Setup:**
   - Initializes serial communication.
   - Configures each connected device (servo, underglow LED, motor, and ultrasonic sensors).
   - Sets up Bluetooth communication with the mobile device.

2. **Loop:**
   - Continuously reads commands sent via Bluetooth.
   - Processes commands to control the underglow LED (turn it on or off).
   - Sends sensor data (e.g., distance) to the mobile device at regular intervals.

## Commands

- `underglow on`: Turns on the LED underglow.
- `underglow off`: Turns off the LED underglow.
