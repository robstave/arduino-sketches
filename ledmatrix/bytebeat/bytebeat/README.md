# Bytebeat Visualizer with Joystick Control

## What This Project Does

This sketch creates real-time audio waveform visualizations on the Arduino UNO R4's LED matrix using mathematical formulas called "bytebeat." The visualization scrolls across the display like a waveform analyzer, and you control it entirely with a joystick.

## Hardware Required

- **Arduino UNO R4 WiFi** (with built-in 8x12 LED matrix)
- **Analog Joystick Module** with button
  - VCC → 5V
  - GND → GND
  - VRx → A0 (X-axis: scene selection)
  - VRy → A1 (Y-axis: scroll speed)
  - SW → A2 (Button: reset pattern)

## How It Works

### Bytebeat Formulas

The code contains 8 different bytebeat "scenes" - mathematical formulas that generate interesting patterns:

1. **Crowd** - Viznut's original. Grinding, rhythmic, iconic.
2. **Sierpinski Harmony** - Fractal triangles, two interleaved melodies.
3. **42 Melody** - Surprisingly musical from a tiny expression.
4. **Tejeez** - Smooth descending cascade with volume envelope.
5. **Chip-tune** - Old-school video game vibes.
6. **Three-voice** - Three layered voices, algorithmic choir.
7. **FM Madness** - Clean 6-bit patterns, parabolic waveform.
8. **Lost in Space** - Spacey, ambient, hypnotic.

### Visualization

Each tick of the pattern:
- Evaluates the formula to get a byte value (0-255)
- Each of the 8 bits maps to one row of the display (bit 7 = top, bit 0 = bottom)
- The display scrolls left by one column
- The new byte appears on the rightmost column
- Creates a real-time waveform visualization

## Controls

### Joystick X-Axis (Left/Right) - Scene Selection
- **Push joystick LEFT** → Switch to the previous scene (cycle backwards through 8 patterns)
- **Center** → Current scene continues
- **Push joystick RIGHT** → Switch to the next scene (cycle forwards through 8 patterns)

When you switch scenes, the pattern restarts and the display clears.

### Joystick Y-Axis (Up/Down) - Scroll Speed
- **Push UP** → Faster scroll speed (10ms per column)
- **Center** → Medium speed (40ms per column, default)
- **Push DOWN** → Slower scroll speed (80ms per column)

Changing the speed lets you see fast, frenetic patterns or slow, meditative ones.

### Joystick Button - Reset Pattern
- **Press button** → Reset the time counter to 0 and clear the display
- Current scene stays the same, just restarts from the beginning
- Great for restarting a pattern you like or getting out of visual chaos

## Try These Modifications

### Beginner Level
1. Change `scrollDelay` default values to try different default speeds
2. Add more bytebeat formulas to the switch statement
3. Modify the zone thresholds (300 and 723) for joystick sensitivity

### Intermediate Level
1. Add serial output to print the current formula name
2. Create a "cycle auto mode" that changes scenes automatically
3. Adjust the speed range (currently 10-80ms) to experiment with perception

### Advanced Level
1. Add Y-axis control to select scenes (use both X and Y for a 2D menu)
2. Implement a "speed sweep" that gradually changes scroll speed
3. Create custom bytebeat formulas and add them to the 8 existing ones
4. Add brightness control using PWM on an external LED strip

## Understanding Bytebeat

Bytebeat is a technique for generating music using simple mathematical expressions. By combining:
- Time counters
- Bitwise operations (`&`, `|`, `^`, `>>`, `<<`)
- Modulo and division
- Multiplication and addition

You can create surprisingly complex and musical patterns from just one or two lines of code!

The byte value generated at each time step was originally used for raw 8-bit audio output. Here, we use it as a visual waveform where each bit controls one row of the matrix.
