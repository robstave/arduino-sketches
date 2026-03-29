# Alphanumeric LED Matrix Display

## 🎯 What This Project Does

This Arduino sketch displays numbers (0-9) and letters (A-Z) on the Arduino UNO R4's built-in LED matrix display. Each character appears on the screen for one second before moving to the next one.

## 🛠️ Hardware Required

- **Arduino UNO R4 WiFi** (the board with the built-in 8x12 LED matrix)

## 📚 What You'll Learn

- How to use the Arduino LED Matrix library
- Working with 2D arrays to represent pixel data
- Using custom fonts stored in header files
- Binary numbers and bit manipulation
- Character encoding (ASCII)
- Functions and modular programming

## 🔧 How It Works

### The LED Matrix

The Arduino UNO R4 has a built-in LED matrix with **8 rows** and **12 columns** of LEDs (96 LEDs total!). We can turn each LED on or off to create patterns, letters, and numbers.

### The Frame Buffer

The `frame[8][12]` array is like a grid that represents the LED matrix:
- Each row has 12 values (one for each LED column)
- Each value is either `0` (LED off) or `1` (LED on)

### Custom Fonts

The [fonts.h](fonts.h) file contains pixel patterns for each character. Each character is defined as 8 rows of binary numbers:
- `0b01110` represents a row where LEDs at positions 2, 3, and 4 are on
- These patterns are based on the font from [ArduinoGetStarted.com](https://arduinogetstarted.com/tutorials/arduino-uno-r4-led-matrix-displays-number-character)

## 📖 Code Overview

### Main Functions

1. **`setup()`** - Runs once when the Arduino starts
   - Initializes serial communication for debugging
   - Starts the LED matrix

2. **`loop()`** - Runs continuously
   - Displays numbers 0-9, one per second
   - Displays letters A-Z, one per second
   - Repeats forever

3. **`clear_frame()`** - Sets all LEDs to off (fills the frame with zeros)

4. **`display_frame()`** - Sends the current frame to the LED matrix

5. **`add_to_frame(char c, int pos)`** - Draws a character at a specific position
   - Looks up the character pattern in the fonts array
   - Uses bit shifting to position the character horizontally
   - Uses the OR operator (`|=`) to add the character to the frame

## 💡 Try These Modifications

### Beginner Level
1. Change the delay time to make characters display faster or slower
2. Display only numbers (remove the letters loop)
3. Display only vowels: A, E, I, O, U

### Intermediate Level
1. Add lowercase letters to the font
2. Display your name or initials
3. Create a scrolling message across the screen
4. Add special characters like `!` or `?`

### Advanced Level
1. Modify the `add_to_frame()` function to scroll text horizontally
2. Create animations by modifying characters over time
3. Add user input via Serial Monitor to display custom messages
4. Create a simple game using the LED matrix

## 📝 Understanding Bit Operations

The code uses binary (base-2) numbers and bitwise operations:

```cpp
0b01110  // Binary: 5 bits, reads as "01110"
         // Represents: [OFF, ON, ON, ON, OFF]
```

**Left shift (`<<`)**: Moves bits to the left (multiplies by 2)
```cpp
0b00011 << 2 = 0b01100  // Shifted 2 positions left
```

**OR operator (`|=`)**: Combines bits (turns LEDs on without turning off existing ones)
```cpp
0b01010 | 0b00110 = 0b01110
```

## 🔗 Resources

- **Font Source**: [ArduinoGetStarted.com LED Matrix Tutorial](https://arduinogetstarted.com/tutorials/arduino-uno-r4-led-matrix-displays-number-character)
- [Arduino UNO R4 WiFi Documentation](https://docs.arduino.cc/hardware/uno-r4-wifi)
- [Arduino LED Matrix Library Reference](https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix)

## 📄 License

This code is in the public domain. Feel free to use and modify it for your own projects!

---

**Happy Making! 🚀**
