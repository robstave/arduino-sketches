# LED Matrix Projects

Sketches featuring the built-in LED matrix on the Arduino UNO R4 WiFi.

## Project Overview

| Sketch | Readme | Requirements |
|--------|--------|--------------|
| **Display & Text** | | |
| alphanum | [alphanum/README.md](alphanum/README.md) | None |
| bytebeat | [bytebeat/README.md](bytebeat/README.md) | None |
| **Animations** | | |
| car-driving | [car-driving/README.md](car-driving/README.md) | None |
| visual1 | [visual1/README.md](visual1/README.md) | Joystick |
| **Interactive** | | |
| eyeball | [eyeball/readme.md](eyeball/readme.md) | Joystick |
| starfield | [starfield/readme.md](starfield/readme.md) | None (starfield1), Joystick (starfield2/3) |

## About the LED Matrix

The Arduino UNO R4 WiFi includes a built-in **12×8 LED matrix** (96 LEDs total) that can display:
- Text and numbers
- Animations and graphics
- Interactive visualizations
- Games and effects

Each LED is either fully ON or OFF - there's no brightness control (PWM) for individual pixels. This means effects rely on patterns, movement, and clever timing rather than fading or dimming.

## Bill of Materials (BOM)

### Core Hardware
- **Arduino UNO R4 WiFi** - Required for all projects

### Optional Components

| Component | Used In | Notes |
|-----------|---------|-------|
| Analog Joystick Module | eyeball, starfield2, starfield3, visual1 | 5-pin module with X/Y axis + button |
| Jumper Wires | Interactive projects | Male-to-male or male-to-female |

### Joystick Wiring

When a joystick is required, use this standard connection:

| Joystick Pin | Arduino Pin | Description |
|--------------|-------------|-------------|
| VCC | 5V | Power |
| GND | GND | Ground |
| VRx | A0 | X-axis analog output |
| VRy | A1 | Y-axis analog output |
| SW | A2 | Button (switch) |

**Note:** The button uses `INPUT_PULLUP` mode - it reads LOW when pressed, HIGH when released.

## Getting Started

1. **Pick a project** - Start with simpler ones like `alphanum` or `car-driving`
2. **Read the project README** - Each folder has detailed instructions
3. **Upload the sketch** - Open the `.ino` file and upload to your UNO R4
4. **Experiment** - The real learning happens when you modify the code!

## Learning Path

### Beginner
- **alphanum** - Display text and understand the frame buffer concept
- **car-driving** - Simple sprite animation

### Intermediate  
- **eyeball** - Joystick input and interactive graphics
- **starfield1** - Basic 3D projection and motion
- **bytebeat** - Audio-driven visuals

### Advanced
- **starfield2/3** - Full 3D control with camera movement and projectiles
- **visual1** - Understanding hardware limitations and creative workarounds

## Resources

- [Arduino UNO R4 WiFi Documentation](https://docs.arduino.cc/hardware/uno-r4-wifi)
- [Arduino LED Matrix Library Reference](https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix)
- [Arduino Language Reference](https://www.arduino.cc/reference/en/)

---

**Light up your learning!**
