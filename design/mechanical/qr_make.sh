#!/bin/bash
qrencode --verbose --svg-path -iv 2 --strict-version -l L -t SVG --background=00000000 --foreground=FFFF00 -o qr.svg "https://github.com/ColoMAX/fishfeeder"
