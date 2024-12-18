# Remote-Controlled Boat

## Table of Contents
- [Introduction](#introduction)
- [Hardware Components](#hardware-components)
- [Software Components](#software-components)
- [Functional Description](#functional-description)
- [Operation Modes](#operation-modes)
- [Implementation Details](#implementation-details)
- [Experimental Results](#experimental-results)
- [Conclusions and Future Work](#conclusions-and-future-work)
- [Appendix](#appendix)
- [References](#references)

---

## Introduction

This project showcases a remote-controlled boat powered by a 9V battery. The boat utilizes an infrared sensor for remote communication, allowing seamless control over its movement. A DC motor, managed via an L293D motor shield, propels the boat, while a servo motor enables precise steering. The system is designed for simplicity and efficiency, making it an excellent demonstration of integrating basic components to achieve functional remote-controlled navigation. This project serves as a foundation for exploring advanced control mechanisms and alternative power solutions in future iterations.

---

## Hardware Components

| **Component**         | **Quantity** | **Role**                             | **Datasheet/Link**        |
|------------------------|--------------|--------------------------------------|---------------------------|
| Arduino Nano           | 1            | Main microcontroller                 | [Arduino Nano](https://docs.arduino.cc/hardware/nano) |
| L293D Motor Driver     | 1            | Controls the DC motor                | [L293D Datasheet](https://www.ti.com/lit/ds/symlink/l293.pdf) |
| Infrared Sensor        | 1            | Captures remote input                | [IR Sensor Datasheet](https://components101.com/sensors/ir-sensor-module) |
| DC Motor (RF-310T-11400) | 1          | Provides forward propulsion          | [RF-310T Datasheet](https://www.alldatasheet.com/datasheet-pdf/pdf/1262796/PROMOCO/RF-310TA-11400.html) |
| Servo Motor (SG90)     | 1            | Enables steering                     | [SG90 Datasheet](https://servodatabase.com/servo/towerpro/sg90) |
| 9V Battery             | 1            | Powers the system                    | N/A                      |
| Power Switch           | 1            | Turns the system ON/OFF              | N/A                      |
| Wires and Connectors   | Multiple     | Connects components                  | N/A                      |

---

## Software Components

- **Arduino IDE**: Used for programming the Arduino Nano.
- Code for processing infrared input, motor control, and servo operations.

---

## Functional Description

The remote-controlled boat operates as follows:

1. **Infrared Sensor**: Captures signals from a remote control and sends them to the Arduino Nano via **A1**.
2. **L293D Motor Driver**: Manages the DC motor for propulsion:
   - **Control Pin 1**: Connected to **D9** for motor control.
   - **Input 1**: Connected to **D8** for motor direction.
   - **Input 2**: Connected to **D7** for motor direction.
3. **Servo Motor (SG90)**: Connected to **D6** for steering the boat.
4. **Power Supply**: A 9V battery powers the Arduino Nano and motor driver through **Vin** and **GND**, with a switch to enable or disable the system.

---

## Operation Modes

1. **Forward Movement**: The Arduino Nano controls the DC motor using the L293D driver.
2. **Steering**: The SG90 servo motor rotates to adjust the boat’s direction based on input from the infrared sensor.
3. **Power Control**: A switch is used to turn the entire system ON or OFF.

---

## Implementation Details

### Pin Connections

| **Component**          | **Pin**     | **Arduino Pin** | **Purpose**                      |
|-------------------------|-------------|-----------------|----------------------------------|
| Power Supply (9V)       | Vin         | Vin             | Main power input                 |
| L293D Motor Driver      | Power 1 (9) | 5V              | Power for motor logic            |
|                         | Control 1,2 | D9              | Motor control signal             |
|                         | Input 1     | D8              | Motor direction input            |
|                         | Input 2     | D7              | Motor direction input            |
|                         | Output 1    | DC Motor +      | Motor connection                 |
|                         | Output 2    | DC Motor -      | Motor connection                 |
| Servo Motor (SG90)      | VCC         | 5V              | Power input                      |
|                         | Signal      | D6              | Steering control signal          |
| Infrared Sensor         | VCC         | 5V              | Power input                      |
|                         | Output      | A1              | Signal input to Arduino          |
| Switch                  | Positive    | Power Supply    | System ON/OFF control            |

### Block Diagram

The block diagram illustrates how each component is interconnected:

![Block Diagram](img/Schema%20Bloc.png)

### Electrical Diagram

The electrical schematic details the wiring setup:

![Circuit Diagram](img/Tinkercad.jpg)

---

## Experimental Results

- 

---

## Conclusions and Future Work

- 

---

## Appendix

### Hardware Assembly Photos

1. **Hardware Setup - Full View**  
   ![Hardware Full View](img/Hardware_Full_View.jpg)

2. **Close-up of Key Connections**  
   ![Hardware Close-up](img/Hardware_Closeup.jpg)

---

## References

- [Arduino Nano Documentation](https://docs.arduino.cc/hardware/nano)
- [L293D Datasheet](https://www.ti.com/lit/ds/symlink/l293.pdf)
- [IR Sensor Module](https://components101.com/sensors/ir-sensor-module)
- [RF-310T DC Motor Datasheet](https://www.alldatasheet.com/datasheet-pdf/pdf/1262796/PROMOCO/RF-310TA-11400.html)
- [SG90 Servo Motor Datasheet](https://servodatabase.com/servo/towerpro/sg90)
