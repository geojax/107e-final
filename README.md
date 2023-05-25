# 107e-final
final project from the Stanford course cs107e

# This is an emulation of the PICO-8 fantasy console on bare-metal Raspberry Pi.
The PICO-8 screen resolution and color palette have been both translated onto the Raspberry Pi. In addition, the client interface in PICO-8 has been kept as loyally as possible so that developing in this library feels almost identical to developing with PICO-8. Clients pass in their own init, draw, and update functions to the 'console' (see include/pico.h) and the emulation targets 30FPS just like PICO-8 does.

This is also the skeleton of a top-down Zelda-like game.
In this version, input, movement, collision, enemy behavior, and animations are all functional. This depends on the Raspberry Pi module coded in the course CS107e for graphics.

### main.c/h
does nothing.

### starting file: test/complete_test.c
My contributions:
- fast drawing: the Raspberry Pi took a very long time to redraw the screen. To work around this, only the four tiles around the player and around every enemy were redrawn every frame.
- player movement and collision with map
- map drawing
- sprite storage, representation, and drawing
- tools for designing sprites and maps in PICO-8 and pasting them as text into a .c file (see include/sprite.c and include/map.c for functions that take these strings as input)
- art (sprites and map tiles)
- state-based animation of player
- PICO8-style structure 

### Context
This project was completed with a partner at the end of CS107e Computer Systems from the Ground Up. CS107e is a renowned course in which students learn systems programming on a bare-metal Raspberry Pi. The first 8 weeks of the course revolve around developing a module to interface with the Pi, including a console, shell, and graphics library. String functions like printf are also coded from scratch, as well as a backtrace function. 

https://github.com/geojax/107e-final/assets/50026101/db29e683-f58f-49f8-af52-780612417e11

