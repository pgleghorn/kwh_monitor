#!/bin/sh

arduino-cli compile -b arduino:avr:mega LightSensor.ino 
arduino-cli upload -b arduino:avr:mega -p /dev/ttyACM0 LightSensor.ino
