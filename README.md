# worm_bot
A robot intended to carry a worm for wireless sniffing and other fun stuffs

**This is far from done; right now it is just controlling the servos at a low level**

## TODO List
* Validate input from serial.
* Implement walking functions and serial commands.
* Move to it's own board.
* Setup serial connection from Raspberry Pi to board.
* Design and 3D print robot body and walking mechanism.
* Add camera module to Pi.
* Make web interface with socket connection to Pi using NodeJS.
* Add cellular radio to Pi for remote control?

## Board Setup
I am using an Arduino Uno for this project

* First servo data pin: 9
* Second servo data pin: 8
* Serial Baud rate: 57600


## Serial Commands
Currently there is only one command; this sets the position of the first and second servo respectively.

### Example
```
# 120,40
```
This sets the location of the first servo to "120" and the second to "40"
