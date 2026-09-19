# RFID Access Control System

> An Arduino-based RFID access control prototype for granting or denying entry using authorized RFID cards, visual indicators, an LCD display, and audio feedback.

[![Platform: Arduino](https://img.shields.io/badge/platform-Arduino-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Language: C++](https://img.shields.io/badge/language-C%2B%2B-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

## Overview

This project reads RFID card UIDs with an **MFRC522 reader**, checks them against a list of authorized cards, and provides immediate feedback through a **16×2 I2C LCD**, LEDs, and a buzzer.

It supports both:

- **Unlimited-use cards** for permanent access.
- **Limited-use cards** that expire after a configurable number of successful scans.

> **Important:** This is an educational prototype. RFID UID-only authentication should not be used as the sole security mechanism for a production access-control system because card UIDs can be copied or spoofed.

## Features

- ✅ RFID card scanning and UID formatting
- ✅ Allowlist-based access verification
- ✅ Unlimited and limited-use cards
- ✅ Configurable usage limit (default: 20 uses)
- ✅ LCD status messages for access decisions
- ✅ Green LED and short beep for granted access
- ✅ Red LED and repeated beeps for denied access
- ✅ Serial Monitor logging at 9600 baud
- ✅ No external database or network connection required

## Hardware

| Component | Purpose |
| --- | --- |
| Arduino Uno or compatible board | Main microcontroller |
| MFRC522 RFID reader | Reads RFID card/tag UIDs |
| 16×2 LCD with I2C backpack | Displays system messages |
| Green LED | Indicates granted access |
| Red LED | Indicates denied access |
| Buzzer | Provides audio feedback |
| Resistors and jumper wires | LED protection and connections |

## Wiring

### Control pins

| Component | Arduino pin |
| --- | ---: |
| MFRC522 SDA / SS | `10` |
| MFRC522 RST | `9` |
| Green LED | `2` |
| Red LED | `3` |
| Buzzer | `4` |

### Interfaces

- **MFRC522:** SPI interface
- **LCD:** I2C interface, default address `0x27`
- **Serial Monitor:** `9600` baud

> The Arduino Uno's standard SPI pins are used by the MFRC522 module: MOSI `11`, MISO `12`, and SCK `13`. Connect the module's power according to its datasheet; many MFRC522 boards require **3.3 V**.

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- [MFRC522](https://github.com/miguelbalboa/rfid) library
- `LiquidCrystal_I2C` library
- `SPI.h` and `Wire.h` (included with the Arduino platform)

Install the external libraries through **Arduino IDE → Sketch → Include Library → Manage Libraries**.

## Getting Started

1. Clone or download this repository.
2. Open `RFID.ino` in the Arduino IDE.
3. Install the required libraries listed above.
4. Assemble the circuit using the wiring tables.
5. Select the correct board and port in the Arduino IDE.
6. Upload the sketch to your Arduino board.
7. Open the Serial Monitor at **9600 baud**.
8. Scan a card and observe the LCD, LED, buzzer, and serial output.

## Authorized Cards

The sketch includes these example UIDs:

| UID | Access type |
| --- | --- |
| `2E F3 2D 03` | Limited access — maximum 20 uses |
| `71 8B B0 02` | Unlimited access |

To add or replace cards, update the `allowedUIDs` array in the sketch. Always use the UID format printed by the Serial Monitor.

## How Access Decisions Work

1. The reader detects an RFID card.
2. The sketch converts the card UID into a comparable string.
3. The UID is checked against the configured allowlist.
4. If the card is authorized and has remaining uses, access is granted.
5. If the card is unknown or has expired, access is denied.
6. The LCD, LEDs, buzzer, and Serial Monitor report the result.

## Configuration

- Change `maxUsage` to adjust the limit for limited-use cards.
- Change the LCD address from `0x27` if your I2C backpack uses another address, commonly `0x3F`.
- Update the pin constants if your wiring differs.

## Limitations

- Limited-card usage is stored in volatile memory and resets after a power cycle.
- The project does not include persistent storage, user management, encryption, or remote monitoring.
- The default LCD address and hardware pin assignments may vary between boards and modules.

## Troubleshooting

| Problem | Things to check |
| --- | --- |
| RFID card is not detected | Check 3.3 V power, SPI wiring, `SS_PIN`, and `RST_PIN`. |
| LCD is blank | Confirm I2C wiring and try address `0x3F` instead of `0x27`. |
| LEDs or buzzer do not respond | Verify polarity, resistors, ground, and configured pins. |
| UID does not match | Compare spacing and letter case with the format printed in Serial Monitor. |
| Limited card count resets | This is expected because usage is not persisted across power cycles. |

## Project Structure

```text
.
├── RFID.ino    # Arduino sketch
└── README.md   # Project documentation
```

## Contributing

Contributions are welcome. Fork the repository, create a feature branch, test your changes on compatible hardware, and open a pull request with a clear description of the change.

## License

This project is licensed under the [MIT License](LICENSE).
