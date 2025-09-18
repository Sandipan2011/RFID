# RFID Access Control System

An Arduino-based RFID access control system that reads RFID cards, validates them against a list of allowed UIDs, grants or denies access, tracks usage for limited cards (maximum 20 uses), and provides feedback via an LCD display, LEDs, and a buzzer. One card is configured for infinite access.

## Hardware Components

- **Arduino Board**: e.g., Uno or similar (main microcontroller)
- **MFRC522 RFID Reader Module**: Connected to pins 10 (SS) and 9 (RST) for reading RFID cards
- **16x2 LCD Display with I2C Backpack**: Address 0x27, for displaying messages
- **Green LED**: Connected to pin 2, indicates access granted
- **Red LED**: Connected to pin 3, indicates access denied
- **Buzzer**: Connected to pin 4, for audio feedback

## Libraries Used

- `SPI.h`: For SPI communication (required for MFRC522)
- `MFRC522.h`: For interfacing with the MFRC522 RFID module
- `Wire.h`: For I2C communication (required for LCD)
- `LiquidCrystal_I2C.h`: For controlling the I2C LCD display

## Pin Configuration

- SS_PIN: 10 (MFRC522)
- RST_PIN: 9 (MFRC522)
- GREEN_LED: 2
- RED_LED: 3
- BUZZER: 4

## Functionality

- Scans RFID cards and converts the UID to a string format.
- Checks the scanned UID against a predefined list of allowed UIDs.
- For valid cards:
  - Grants access.
  - Displays "Access Granted" on the LCD.
  - Shows remaining uses for limited cards.
  - Lights the green LED and buzzes briefly.
- For invalid or expired cards:
  - Denies access.
  - Displays "Access Denied" and reason on the LCD.
  - Lights the red LED and buzzes repeatedly.
- Uses serial output (9600 baud) for debugging and logging card UIDs and access events.

## Allowed UIDs

The system is pre-configured with two example cards:
- "2E F3 2D 03": Limited access (max 20 uses)
- "71 8B B0 02": Infinite access

You can modify the `allowedUIDs` array in the code to add or change allowed cards.

## Dependencies

- Arduino IDE (for compiling and uploading the sketch)
- MFRC522 library (install via Arduino Library Manager)
- LiquidCrystal_I2C library (install via Arduino Library Manager)

## Power Requirements

- Standard Arduino power supply (5V recommended).
- Ensure the LCD and RFID module are powered appropriately (check datasheets for voltage/current specs).

## Setup Instructions

1. Connect the hardware components as per the pin configuration.
2. Install the required libraries in Arduino IDE.
3. Upload the `RFID.ino` sketch to your Arduino board.
4. Open the Serial Monitor to view debug output.
5. Scan RFID cards to test the system.

## Usage Notes

- The system tracks usage for limited cards and resets on power cycle (no persistent storage).
- Adjust `maxUsage` in the code to change the limit.
- The LCD address (0x27) may need adjustment if your backpack uses a different address (common alternatives: 0x3F).

## License

MIT License

## Contributing

If you'd like to contribute, please fork the repository and submit a pull request.
