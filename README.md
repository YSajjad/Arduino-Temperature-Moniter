# Arduino Temperature Monitor

## Overview
This project is currently a work in progress; the system has been designed but has not yet been physically assembled.

This project is a temperature monitoring system using the DS18B20 digital temperature sensor and the Arduino Uno. Temperatures will be logged over time. The project is designed to leave space for future enhancements.

## Components
- Arduino Uno
- DS18B20 digital temperature sensor
- 4.7 kΩ pull-up resistor
- Piezo buzzer
- 100 µF electrolytic capacitor
- 0.1 µF ceramic capacitor
- LED
- 220 Ω resistor (limits LED current)
- Breadboard and jumper wires

Decoupling is implemented using capacitors. The electrolytic capacitor provides general smoothing, while the ceramic capacitor suppresses high-frequency noise. This helps maintain a stable and reliable system.

## Diagram
Made in tinker CAD
![Circuit Diagram](docs/Temperature%20Sensor%20V1.png)
