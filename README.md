# Bluetooth Based Wireless Smart Toll Barrier using LPC2129

## Project Overview

This project implements a Bluetooth-based wireless smart toll barrier using the LPC2129 ARM7 microcontroller. It combines IR-based vehicle detection, Bluetooth communication, key-based authentication and automatic barrier control.

The system uses an Android mobile phone to send an authentication key wirelessly through an HC-05 Bluetooth module. The LPC2129 validates the received key and controls the toll barrier using an SG90 servo motor.

## Objectives

- Detect vehicles using an IR sensor.
- Establish wireless communication using Bluetooth.
- Implement key-based authentication.
- Display toll information and system status on an LCD.
- Control the toll barrier automatically using a servo motor.

## Features

- Automatic vehicle detection.
- Wireless serial communication using HC-05.
- Predefined authentication key: `1234`.
- Maximum of three authentication attempts.
- LCD-based status display.
- Automatic barrier opening and closing after successful authentication.

## Hardware Requirements

| Component | Purpose |
|---|---|
| LPC2129 ARM7 | Main controller |
| HW-201 IR Sensor | Vehicle detection |
| HC-05 Bluetooth Module | Wireless communication |
| 16×2 LCD | Information display |
| SG90 Servo Motor | Barrier control |
| Android Mobile Phone | Authentication input |
| Power Supply | Hardware operation |

## Software Requirements

- Embedded C
- Keil µVision IDE
- Flash Magic
- Android Bluetooth Serial Terminal
- Proteus Design Suite (if used for simulation)

## Pin Configuration

| Peripheral | Signal | LPC2129 Pin |
-------------------------------------
| IR Sensor  | OUT    | P0.16 /EINT0|
| HC-05      | TXD    | P0.1 / RXD0 |
| HC-05      | RXD    | P0.0 / TXD0 |
| LCD        | D4–D7  | P0.4–P0.7   |
| LCD        | RS     | P0.8        |
| LCD        | E      | P0.9        |
| Servo      | Signal | P0.21 / PWM5|

## Working Principle

1. The IR sensor detects a vehicle near the toll barrier.
2. The LPC2129 receives the detection signal through an external interrupt.
3. The LCD displays the vehicle detection status and toll amount of Rs. 50.
4. Toll information is transmitted to the Android mobile phone through the HC-05 Bluetooth module.
5. The user enters the predefined authentication key through a Bluetooth terminal application.
6. The LPC2129 receives and validates the entered key.
7. If the key is correct, the servo motor opens the barrier.
8. After five seconds, the barrier closes automatically.
9. If authentication fails three times, access is denied and the barrier remains closed.

## Repository Structure

```text
Bluetooth-Based-Wireless-Smart-Toll-Barrier/
│
├── Source_Code/
│   ├── main.c
│   ├── ir_sensor.c
│   ├── ir_sensor.h
│   ├── lcd.c
│   ├── lcd.h
│   ├── uart.c
│   ├── uart.h
│   ├── servo.c
│   └── servo.h
│
├── Circuit_Diagram/
├── Documentation/
├── Media/
│   ├── Images/
│   └── Videos/
│
└── README.md
```

## Testing

Individual hardware modules have been tested:

- IR sensor
- UART communication
- HC-05 Bluetooth communication
- LCD interfacing
- Servo motor control

Complete system integration testing and final hardware verification are to be documented after end-to-end testing.

## Future Scope

- Dynamic OTP generation.
- Online payment gateway integration.
- Digital toll transaction records.
- RFID-based vehicle identification.
- Number plate recognition.

## Project Information

**Project Title:** Bluetooth Based Wireless Smart Toll Barrier using LPC2129

**Microcontroller:** LPC2129 ARM7

**Programming Language:** Embedded C

**Communication:** UART and Bluetooth

**Controller Output:** PWM5

---

**Note:** This implementation currently uses a predefined authentication key. It does not implement dynamic OTP generation or an online payment gateway.
