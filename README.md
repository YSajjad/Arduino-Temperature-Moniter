# Arduino Temperature Monitor

## Overview
This project is a temperature monitoring system using the DS18B20 digital temperature sensor and the Arduino Uno. Temperatures will be logged over time. The project is designed to leave space for future enhancements.
The OneWire and DallasTemperature libraries are used for the sensor.
Version 2 is planned to have Wifi logging, battery pack and an LCD.

## Components
- Arduino Uno
- DS18B20 digital temperature sensor
- 4.7 kΩ pull-up resistor
- Piezo buzzer
- 100 µF electrolytic capacitor
- 0.1 µF ceramic capacitor
- LED & Current limiting resistor
- Breadboard and jumper wires

Decoupling is implemented using an electrolytic and ceramic capacitor for low and high frequency noise.

## Diagram
Made in tinker CAD, note that due to tinker CAD component limitations there is no DS18B20 model hence a TMP36 model is used as a place holder
![Circuit Diagram](docs/Temperature%20Sensor%20V1.png)

## Version 1 Breadboard
Note that the DS18B20 sensor used has a bulit in pull up resistor hence no pull up resistor is included on the breadboard.
![Breadboard](src/v1_local_alarm/V1TemperatureAlarm.jpg)
