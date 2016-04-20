# RedBearLab Wifi Micro Base Project for Code Composer Studio

This repository contains a Code Composer Studio project that can be used as a starting point for developing applications 
for RedBearLab's CC3200 [Wifi Micro](http://redbear.cc/wifi-micro/) (and other CC3200 products).

## Usage

1. Download and install [CCS](http://www.ti.com/tool/ccstudio), [CC3200 SDK](http://www.ti.com/tool/cc3200sdk?keyMatch=cc3200%20sdk&tisearch=Search-EN-Everything) and (optionally) [Uniflash](http://www.ti.com/tool/Uniflash?keyMatch=uniflash&tisearch=Search-EN-Everything).
2. Fork the repository and import it into CCS.
3. Build (either Release or Debug configuration).
4. Program the device either using Uniflash or the cc3200prog program from Energia.
5. Modify and add functionality.

## Content

The project includes the very basic boilerplate needed for CC3200 application development. It has an interrupt table, basic initialization and
Pin Mux definition (Identical to the WiFi Micro board, All digital pins are input and 3 analog inputs). It also has a buffered serial console
(output only) facility to enable quick debugging.
When programmed (unchanged) into the board, the user LED should blink and a repetitive message should appear on the serial console.
