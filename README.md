RFID Door Lock System
This Arduino project implements a simple RFID door lock system using an MFRC522 RFID reader, a servo motor, a relay, and a passive infrared (PIR) sensor.

Components Used:
MFRC522 RFID Reader
Servo Motor
Relay Module
Passive Infrared (PIR) Sensor


Library Installation:
Install the necessary libraries: SPI.h, MFRC522.h, Servo.h, and LiquidCrystal_I2C.h.
These libraries are required to communicate with the RFID reader, servo motor, and LCD screen.


Usage:
RFID Tag Authorization:
Program the authorized RFID tag UID into the code.
Tap the authorized RFID tag on the reader to unlock the door.
Door Lock Mechanism:
When an authorized RFID tag is detected, the servo motor unlocks the door by rotating to a predefined angle.
The relay module controls the locking mechanism, allowing or denying access based on the RFID tag's authorization.
Sensor Integration:
The PIR sensor detects motion near the door.
If motion is detected, the relay module activates, allowing the door to be unlocked if an authorized RFID tag is presented.
LCD Display:
The LCD screen displays status messages such as "Scan Your RFID" and "Door Locked" to indicate system status.


This project is licensed under the MIT License.
Acknowledgments:
Special thanks to the authors of the libraries used in this project for their contributions to the Arduino community
