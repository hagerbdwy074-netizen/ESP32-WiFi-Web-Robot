# ESP32-WiFi-Web-Robot

# 🤖 ESP32 Wi-Fi Web-Controlled Robot

An embedded C++ firmware that turns an ESP32 microcontroller into a self-hosted Wi-Fi Access Point (AP) serving an interactive web interface for real-time mobile robot directional control.

---

## ✨ Features

* 📶 **Standalone Access Point Mode**: Generates its own Wi-Fi network without requiring an external router.
* 🌐 **Built-in Web Server**: Serves a mobile-responsive UI with touch buttons directly from the ESP32.
* ⚡ **PWM Speed & Directional Control**: Manages dual DC motors via an L298N motor driver module.
* 🛡️ **Lightweight & Fast**: Pure C++ implementation using core ESP32 `WiFi.h` library without external UI dependencies.

---

## 🛠️ Hardware Requirements

* **Microcontroller**: ESP32 Development Board
* **Motor Driver**: L298N Dual H-Bridge Motor Driver
* **Actuators**: 2x DC Motors with wheels (Differential Drive Chassis)
* **Power Source**: 2x 18650 Li-ion batteries (7.4V) or suitable DC supply
* **Miscellaneous**: Jumper wires and chassis

---

## 🔌 Circuit Pinout

| L298N Pin | ESP32 Pin | Function |
| :--- | :--- | :--- |
| **ENA** | GPIO 4 | Motor A Speed Control (PWM) |
| **IN1** | GPIO 12 | Motor A Direction 1 |
| **IN2** | GPIO 14 | Motor A Direction 2 |
| **ENB** | GPIO 5 | Motor B Speed Control (PWM) |
| **IN3** | GPIO 26 | Motor B Direction 1 |
| **IN4** | GPIO 25 | Motor B Direction 2 |

---

## 🚀 How to Run

1. **Upload Code**:
   * Open the `.ino` sketch in **Arduino IDE**.
   * Select your board: `Tools > Board > ESP32 Arduino > ESP32 Dev Module`.
   * Upload the sketch to your ESP32.

2. **Connect to Wi-Fi**:
   * Turn on the robot power supply.
   * On your phone or laptop, scan for Wi-Fi networks and connect to:
     * **SSID**: `Hager_Robot`
     * **Password**: `12345678`

3. **Open Control Panel**:
   * Open any web browser and navigate to `http://192.168.4.1`.
   * Use the on-screen directional buttons (**Forward**, **Backward**, **Left**, **Right**, **Stop**) to control the robot.

---
