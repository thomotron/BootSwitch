# BootSwitch
A serial-fed operating system selector switch for GRUB built on the ATTiny85.

This will listen for a phrase being sent in over serial and send a series of keystrokes back if it picks up the correct phrase.

# Why?
I run both Linux and Windows simultaneously on my main PC using GRUB2 as my bootloader.
By default GRUB will boot into Linux, but I have to wait ~10s from powering on before GRUB will let me choose my OS.
I'd much rather flip a switch and walk away while it boots into my OS of choice, so here we are.

# Requirements
This is built to run on an ATTiny85 connected to an MSI Z97S Krait Edition motherboard through the JCOM1 header. It might work with other boards, YMMV.

You'll need:
- An ATTiny25/45/85
- A PC with a serial port
- A MAX232 (optional, for logic level conversion)
- An ISP that can flash an AVR (I used a USBtinyISP)
- `make`
- `avrdude`
- `avr-gcc` and `avr-libc`

# Building
Open the `Firmware` directory and run `make`.

There are a couple of make targets:  
`make fuse`: Burns the fuses into the AVR  
`make flash`: Flashes the firmware  
`make clean`: Cleans up build artifacts

Chip-specific settings (fuses, clock speed, ISP, etc.) are defined in the makefile and should be modified to suit your environment.
