---
author: colomax
date: 14-01-2024
---
# FishFeeder

Standalone automatic fish feeder, based on a ESP8266 with esphome.
![](assets/pictures/skyview.png)


## Installation

### Requirements

- [esphome](esphome.io) (version 2023.11.6)

### Instructions

- Add your modifications to the configuration in `src/fish_feeder.yaml`.
- run: `cd src/; esphome run --device /dev/ttyUSB0 fish_feeder.yaml `
- Then connect to wifi access point, or go to the webserver to configure it.

## Building

### BOM

- esp8266 (Wemos D1 mini)
- 2 SG90 micro Servo's
  - one of which needs to be modified for continues rotation:
    - remove rotation limit on one of the gears
    - De-solder internal potentiometer and add two equivalent resistors, to fool controller in always center position, but keep potentiometer in there, for structural support of gears.
- 3d printer and some (food-safe) filament
- laser/water cutter with 3mm flat material
- vibration motor (Seeed Studio 316040001)
- stsp momentary switch
- hot glue
- metal binding wire (for hinges and lid opening)
- 8x1 pin-header or other connector
- 2x m2 bolts
- Plexiglass

### Instructions

- 3D print the screw and bucket (`design/mechanical/*.3mf`)
- Laser-cut the casing (`design/mechanical/Laser_cut_box.svg`)
- Solder as described in `design/electrical/schematic.svg`.
- Use wire and the small pieces from the cutter to create the hinges
- Screw the continues servo to the bucket
- Heat the end of the screw in order to press-fit it to the servo
- Glue to other servo on a 90 degree angle to the previous one

## TODO

- test code: daylight saving switch
- custom css
- Add light control (timer)
