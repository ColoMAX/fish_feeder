#!/bin/bash
qrencode --verbose -iv 1 -l L -t SVG --background=00000000 --foreground=FFFF00 -o qr.svg "https://github.com/ColoMAX/fish_feeder"
