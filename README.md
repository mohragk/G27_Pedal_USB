# 10-bit G27/G29 USB adapter script for Arduino boards
Simple arduino code for interfacing G27/G29 pedals via USB.

## Auto-calibration
The script auto-calibrates the pedal output. The potentiometers in the pedal board might 
not output a full 0 - 1023 range, so the output is automatically mapped to output a full 10-bit range. 
When first connected, it's important to depress all pedals fully to initially set this range.

## Joystick library
This script uyses the following [Joystick library](https://github.com/MHeironimus/ArduinoJoystickLibrary ) so make sure this is installed in your Arduino IDE. DON'T USE THE BUILT-IN JOYSTICK LIBRARY THAT'S INCLUDED WITH ARDUINO!
