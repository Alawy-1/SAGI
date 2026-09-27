# Plant Irrigation System 
- This project senses the soil of a specific plant to irrigate it automatically without human intervention, while still getting updates remotely about the soil moisture degree.

## How to upload 
- install Arduino IDE
- connect the project circuit to the computer
- upload the .ino file to the ESP32 microcontroller

## Hardware Components
- ESP32-s3
- LED
- Pump
- breadboard
- relay
- soil moisture sensor

## How it works
- gets soil moisture level
- decides wether to irrigate or not depending on the threshold
- updates the soil moisture level through the root webpage

## Future work
- add a camera to view the plant health
- add more routes and features that could be preformed remotely
- moving robot that irrigates more than one plant
- use weather api to enhance the irrigation system
