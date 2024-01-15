# Overview

## Requirements

- [Install ESPHome](www.esphome.io) (version 2023.11.6)

## Customization

One can customize this project with ease. A few examples are:

- Instead of ESP8266, use an ESP32 (or variants). For this one would need to substitute `esp8266_pwm` with `ledc` in the yaml file, and change the board.
- Add RGB lighting and heating control by adding a temperature sensor and [Climate controller ESPHome software component](https://esphome.io/components/climate/bang_bang).
- Add graphics to your box by modifying the laser cutter files.
- Add custom lighting effects to mimic a sunrise using [RGB-leds](https://esphome.io/components/light/rgb.html) and the [ESPHome sun component](https://esphome.io/components/sun.html).
- Etc.

### Software

- Add your modifications to the configuration in `src/fish_feeder.yaml`.
  - e.g.: new name, enable home-assistant integration, add other controls, such as RGB lights.
- connect via usb.
- run: `cd src/; esphome run --device /dev/ttyUSB0 fish_feeder.yaml `
- Then connect to wifi access point, or go to the webserver (by default `http://fishfeeder.local:80`) to configure it.

### Mechanical

Do so to your hearts content, all design files are available in the `design/mechanical` directory. Here you can modify the designs if required. The `3mf` files contain the 3D printed parts, the and the rest should be self evident.

There are some software which you might want to install before continuing.

- [PrusaSlicer](https://www.prusa3d.com/page/prusaslicer_424/) to create the gcode for your printer.
- qrencode by running `apt install qrencode`, for a qr code.
- Inkscape by running `apt install inkscape, to modify the laser cutter design.
- LaserWeb or LightBurn, to create the gcode for your cutter.

To generate a QR to this page, which will be put on the box, run `cd design/mechanical; bash qr_make.sh`.

## Build

### Parts list

- 1x esp8266 (Wemos D1 mini)
- 2x SG90 micro Servo's
  - one of which needs to be modified for continues rotation:
    - remove rotation limit on one of the gears
    - De-solder internal potentiometer and add two equivalent resistors, to fool controller in always center position, but keep potentiometer in there, for structural support of gears.
- 3D printer and some (food-safe PLA) filament (approx 7m/21g of filament)
- laser/water cutter with 3mm flat material
- 1x vibration motor (Seeed Studio 316040001)
- 1x stsp momentary switch
- hot glue
- 2x paperclips or metal binding wire (for hinges and lid opening)
- 1x 8x1 pin-header or other connector
- 2x m2 bolts
- 1x acrylic/Plexiglass (approx 39x83mm)

### Assembly

These instructions are not complete, but should give you the general idea, be creative!

- 3D print the screw and bucket (`design/mechanical/*.3mf`)
- Laser-cut the casing (`design/mechanical/Laser_cut_box.svg`)
- Solder as described in `design/electrical/schematic.svg`.
- Use wire and the small pieces from the cutter to create the hinges
- Screw the continues servo to the bucket
- Heat the end of the screw in order to press-fit it to the servo
- Glue to other servo on a 90 degree angle to the previous one
- Add the headers and hinge and wires between hinge, servo and your aquarium lid.
- Close it all up.

Now continue with [Getting started](getting-started.md).
