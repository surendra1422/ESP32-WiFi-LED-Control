# ESP32 WiFi LED Controller

A simple ESP32 project that creates its own WiFi hotspot and provides a web page to control four LEDs from a mobile phone.

## Project Name

**UR.SURENDRA - ESP32 LED Controllers**

## Features

- ESP32 creates a WiFi access point named `ESP32_LED`
- Password-protected WiFi connection
- Mobile-friendly web control page
- Control four LEDs independently:
  - Red LED
  - Blue LED
  - Green LED
  - White LED
- ON/OFF switches for each LED

## Components Required

- ESP32 development board
- Red LED
- Blue LED
- Green LED
- White LED
- 4 × current-limiting resistors
- Jumper wires
- Breadboard

## Pin Connections

| LED | ESP32 GPIO |
|---|---:|
| Red LED | GPIO 25 |
| Blue LED | GPIO 26 |
| Green LED | GPIO 27 |
| White LED | GPIO 33 |

## WiFi Details

- **WiFi Name:** `ESP32_LED`
- **Password:** `12345678`

The ESP32 works in WiFi Access Point (AP) mode.

## How It Works

The ESP32 runs a web server on port 80.

The phone connects to the ESP32 WiFi network and opens the web control page. Each switch sends a request to the ESP32, which turns the corresponding LED ON or OFF.

## Libraries

- WiFi.h
- WebServer.h

## Safety

This project is designed for low-voltage LED experiments.

**Do not connect ESP32 GPIO pins directly to 230V AC household electricity.**

## Author

**UR.SURENDRA**