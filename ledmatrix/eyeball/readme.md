# Eyeball Animation Projects

## 🎯 Overview

This folder contains Arduino sketches that create animated eye effects on the Arduino UNO R4's built-in LED matrix display. These projects combine graphics programming with interactive hardware control using a joystick to create realistic eye movements and animations.

## 🛠️ Hardware Required

- **Arduino UNO R4 WiFi** (the board with the built-in 8x12 LED matrix)
- **Analog Joystick Module** (with X, Y axis outputs and button)
- **Jumper Wires**

## 🔌 Wiring the Joystick

Connect the joystick to your Arduino as follows:

| Joystick Pin | Arduino Pin | Description |
|--------------|-------------|-------------|
| VCC | 5V | Power |
| GND | GND | Ground |
| VRx | A0 | X-axis analog output |
| VRy | A1 | Y-axis analog output |
| SW | A2 | Button (switch) |

**Note**: The button pin uses `INPUT_PULLUP` mode, so it reads LOW when pressed and HIGH when released.

## 📚 What You'll Learn

- Reading analog input from joystick potentiometers
- Mapping analog values (0-1023) to screen coordinates
- Creating organic shapes and animations
- Using mathematical functions for smooth transitions
- Button debouncing and state detection
- Frame-by-frame animation techniques
- Drawing complex graphics with pixel arrays

## 🎨 Projects in This Folder

### eye1 - Joystick-Controlled Eye Tracker

The first project creates an interactive eyeball that:
- **Tracks** the joystick position - move the joystick to make the eye look around
- **Blinks** when you press the joystick button
- Uses smooth animations for realistic eye movements
- Constrains the pupil within a realistic eye shape

[View eye1 documentation →](eye1/readme.md)

### Coming Soon

More eye animation variations are in development, including:
- Automatic eye movements (looking around without joystick)
- Different eye expressions (happy, suspicious, sleepy)
- Multiple eyes with coordinated movement
- Interactive "follow the object" games

## 🔗 Resources

- **Joystick Tutorial**: [Arduino Joystick Guide - ArduinoGetStarted.com](https://arduinogetstarted.com/tutorials/arduino-joystick)
- [Arduino Analog Input Reference](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)
- [Arduino UNO R4 WiFi Documentation](https://docs.arduino.cc/hardware/uno-r4-wifi)
- [Arduino LED Matrix Library](https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix)

## 💡 Understanding Joystick Input

An analog joystick contains two potentiometers (variable resistors):
- **X-axis**: Horizontal movement (left/right)
- **Y-axis**: Vertical movement (up/down)

Each axis outputs a voltage that the Arduino reads as a number from **0 to 1023**:
- **512** = Center (neutral) position
- **0** = Fully left or down
- **1023** = Fully right or up

The `map()` function converts these values into useful screen coordinates.

## 🎓 Advanced Challenges

Once you've mastered the basic eye tracking:
1. Add iris detail (colored ring around the pupil)
2. Make the eye blink automatically every few seconds
3. Create "lazy eye" effect with delayed pupil movement
4. Add eyebrows that react to joystick position
5. Make the pupil dilate/contract based on light sensor input
6. Create two eyes that move together

---

**Happy Making! 👁️**
