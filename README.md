# Bluetooth RC Controller + Arduino Car (Custom PCB)

A wireless joystick controller that drives a motorized car over Bluetooth.

- **Controller (Arduino Uno)** reads two joysticks + buttons and sends commands via **HC-05** Bluetooth.
- **Car (Arduino Nano)** receives commands via a second **HC-05**, controls **two DC motors** through a motor driver, and plays a **buzzer horn**.
- The controller is built on a **custom PCB** designed in **EasyEDA** and manufactured with **JLCPCB**. 

This project was designed end-to-end: electronics, embedded firmware, Bluetooth configuration, PCB layout, assembly, and debugging.

---

## Features
- **2-joystick control**
  - Joystick 1 (vertical): forward / backward
  - Joystick 2 (horizontal): left / right
- **Horn**
  - Click either joystick button to honk (buzzer on the car)
- **Speed stages**
  - Two buttons increase/decrease speed in discrete stages
- **Custom controller PCB**
  - Designed in EasyEDA, ordered via JLCPCB, and hand-assembled/soldered

---

## Hardware
### Controller (TX)
- Arduino Uno
- 2× analog joysticks (with pushbutton)
- 2× pushbuttons (speed up/down)
- HC-05 Bluetooth module
- Power supply (e.g., 9V into Uno)

### Car (RX)
- Arduino Nano
- HC-05 Bluetooth module
- Motor driver + 2× DC motors
- Buzzer (horn)
- Battery/power supply for motors + logic (as required)

---

## Communication Protocol (Controller → Car)
The controller sends single-character commands:

### Direction
- `u` = forward
- `d` = backward
- `l` = turn left
- `r` = turn right

### Horn
- `1` = horn ON (joystick pressed)
- `0` = horn OFF (joystick released)

### Speed stages
- `2` `3` `4` `5` `6` map to increasing PWM levels on the car

In the provided firmware:
- `2` → 75
- `3` → 120
- `4` → 165
- `5` → 210
- `6` → 255

---

## Firmware
### Controller (Arduino Uno)
- Reads joystick analog values and converts them into direction commands using thresholds.
- Reads speed buttons to step speed stage up/down.
- Uses **SoftwareSerial** to talk to HC-05 (9600 baud).
- Uses **ezButton** for joystick pushbutton debouncing.

Key pins (as written in the code):
- Joystick V: A0/A1, button D2
- Joystick H: A2/A3, button D7
- Speed buttons: D11 (up), D10 (down)
- HC-05 SoftwareSerial: D8/D9

### Car (Arduino Nano)
- Receives Bluetooth bytes via **SoftwareSerial** (9600 baud).
- Converts speed-stage commands to PWM levels.
- Drives motor driver pins for forward/back/turning.
- Plays a buzzer tone when horn is pressed.

Key pins (as written in the code):
- HC-05 SoftwareSerial: D8/D7
- Motor control pins: D5, D6, D9, D10
- Buzzer pin: D3

---

## Setup Instructions
### 1) Configure HC-05 modules
You need two HC-05 modules paired to each other (one controller side, one car side). Typical approach:
- Put modules into **AT mode**
- Set one as **master** and one as **slave**
- Pair/bind addresses
- Ensure both use the same serial speed (this project uses **9600**)

(Exact AT commands vary by board/module revision — follow an HC-05 AT-mode guide.)

### 2) Wire everything (use the schematics)
- See `/hardware/schematics/` for:
  - Controller wiring diagram
  - Car wiring diagram

### 3) Upload firmware
- Open `firmware/controller_uno/controller_uno.ino` → upload to **Arduino Uno**
- Open `firmware/car_nano/car_nano.ino` → upload to **Arduino Nano**
- Power both systems, confirm Bluetooth pairing, and test controls.

---

## License
This project is licensed under the MIT License — see the LICENSE file.
