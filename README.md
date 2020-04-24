Frequency counter
=================
This is a design of a simple but powerful frequency counter capable 
of measurements of frequency with 8 digits of precision every second.

This frequency counter is based on a little **PIC 16F18446** a 
16x2 LCD display, and USB-Serial interface with PC.

You can mount it over a breadboard with this simple 
[schematic](pic16f18446/kicad/breadboard/freqcounter_16F18446.pdf)


Specifications
--------------
* Input frequency range: 0.01 Hz to 15MHz
* Resolution: 8 digits per second (10PPB) at all frequencies.
* Precision: 0.1PPM with simple crystal and calibration.
* Number of inputs: 2 TTL inputs + 1 Zero Cross Detection input
* Output: Frequency or Period, time and pulses counted.
* Phase delay: between 2 inputs with 10ns of resolution.
* Gate times: 1 second and 0.1 seconds.
* Output: via LCD and serial UART.
* Autocalibration: with 1PPS signal or with 10MHz signal.
* Continuous timestamp and reciprocal counting internal methods.
* Frequency autorange from Mega Hertz to milli Hertz.
* Adaptable system frequency without reprogramming (8MHz internal or 5MHz external)
* Command Line Interface: via USB-serial communications for configuring options.
* Input levels: between 0.8v (LOW) and 3.1V (HIGH).
* Power Supply: 5 volts.
* DIY: you can mount it with a breadboard and one crystal oscillator.


Licenses
--------

* Creative Commons Atribution-ShareAlike version 4, for hardware designs,
  texts, photograps, layouts, schematics, and similar.

* GNU General Public License version 3, for microcontroller 
  and computer programs.

