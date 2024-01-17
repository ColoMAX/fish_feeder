#!/bin/bash
cp fishfeeder.yaml fishfeeder_esp8266.yaml
patch -p1 < esp32.patch
mv fishfeeder.yaml fishfeeder_esp32.yaml
