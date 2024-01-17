---
author: colomax
date: 14-01-2024
---
# FishFeeder

Standalone automatic fish feeder, based on a ESP8266 with ESPHome.
![](docs/assets/pictures/skyview.png)

Just dispenses (fish) food using a 3D-printed (archimedean) two flute screw. It uses a modified servo motor to drive the screw, such that it no longer has angle limits. A secondary servo is installed to open a lid of the fish tank, as well as a vibration motor to make the dispenses more consistent. An additional relay can be installed to control some form of lighting.

It is intend to be used stand-alone, but because it is written using the ESPHome project, it can easily be integrated in the rest of your home-automation. The device is configured using a web interface, but can also be controlled manually via the push of a button.

Although the project is build using an ESP8266, other controllers supported by ESPHome (esp32, rp2040, ...) can also be used, with minimal modifications.

## Getting started

Take a look at the [docs](https://ColoMAX.github.io/fishfeeder).

## TODO

- custom css
- Add light control (timer)
- ~~Change order in webserver (create pr esphome feature-request #1774)~~ fixed by prefix numbers
