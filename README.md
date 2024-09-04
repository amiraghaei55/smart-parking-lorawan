# Smart Parking System Using LoRaWAN

This project implements a smart parking system using ultrasonic sensors and LoRaWAN communication. The system monitors parking spots and sends the status (occupied/free) to a central gateway over LoRaWAN.

## Features
- Detects if parking spots are free or occupied using ultrasonic sensors.
- Sends parking status over LoRaWAN to a central gateway.
- Designed for low-power and long-range communication using LoRa.

## Hardware
- **Microcontroller**: ESP32 or STM32 with LoRa module.
- **Sensor**: HC-SR04 ultrasonic sensor.
- **LoRa Module**: RAK811 or SX1276 transceiver.
- **LoRa Gateway**: Required for communication with the cloud or dashboard.

## How to Run
1. Flash the code to your STM32 or ESP32.
2. Connect the ultrasonic sensors to the appropriate GPIO pins.
3. View parking status on the serial monitor or through a cloud dashboard.

