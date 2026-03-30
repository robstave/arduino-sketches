# LDR (Light Sensor) Projects

Light-dependent resistor (LDR) experiments using the Flying Fish LDR sensor module. Learn how to read light levels and use them to control your Arduino projects.

## About the Flying Fish LDR Module

The Flying Fish LDR sensor module is a ready-to-use light sensor breakout board that provides both analog and digital outputs. It includes an onboard potentiometer to set a light threshold for the digital output.

### Wiring Diagram

![LDR Wiring Diagram](ldr.png)

### Wiring

| Module Pin | Arduino Pin | Description |
|------------|-------------|-------------|
| VCC | 5V | Power |
| GND | GND | Ground |
| A0 (Analog) | A5 | Analog light level (0-1023) |
| D0 (Digital) | A4 | Digital threshold output (HIGH/LOW) |

**Output LED:** Pin 13 (built-in LED, PWM capable)

## Project Overview

| Sketch | Readme | Description | Hardware |
|--------|--------|-------------|----------|
| flyingfish-debug | [flyingfish-debug/README.md](flyingfish-debug/README.md) | Debugging-focused: Serial Monitor practice | Flying Fish LDR module |
| flyingfishled | [flyingfishled/README.md](flyingfishled/README.md) | LED matrix visualization | Flying Fish LDR + UNO R4 |

## Learning Progression

### 1. [flyingfish-debug](flyingfish-debug/) - Serial Monitor Debugging

**Start here!** Learn how to debug with the Serial Monitor:
- Open Tools → Serial Monitor (or Ctrl+Shift+M)
- Watch the numbers change as you cover/uncover the sensor
- Understand what the sensor "sees" in different lighting conditions
- Learn to read sensor data to troubleshoot projects

**Why this matters:** Most Arduino problems come from sensors giving unexpected values. Learning to watch sensor data in real-time is one of the most important Arduino skills!

### 2. [flyingfishled](flyingfishled/) - LED Matrix Visualization

Visualize your sensor data:
- Displaying data on the Arduino UNO R4's built-in LED matrix
- Visual bar chart showing light level
- Digital indicator showing threshold state
- See your sensor data at a glance without the Serial Monitor

## 💡 What You'll Learn

- **Analog input** - Reading continuous values from sensors
- **Digital input** - Reading binary (on/off) states
- **Mapping values** - Converting sensor ranges to useful outputs
- **PWM output** - Controlling LED brightness
- **Serial debugging** - The #1 skill for troubleshooting Arduino projects
- **Data visualization** - Showing sensor data on LED displays

## 🛠️ Common Issues & Debugging

### Sensor always reads 0 or 1023
- Check your wiring - might be disconnected
- Verify power (VCC and GND) connections

### Digital output doesn't change
- Adjust the onboard potentiometer (small screw on the module)
- Turn clockwise/counter-clockwise to change the threshold
- Watch the analog value in Serial Monitor to see where threshold is set

### LED not changing brightness
- Pin 13 might not support PWM on some boards
- Try a different PWM-capable pin (3, 5, 6, 9, 10, 11)
- Check that `analogWrite()` is being called with values 0-255

### Serial Monitor shows garbage
- Check baud rate matches `Serial.begin()` value (usually 9600)
- Make sure you selected the correct COM port

## 🎯 Project Ideas

Once you master the basics, try:

1. **Light-activated alarm** - Sound a buzzer when it gets dark
2. **Automatic night light** - Turn on LEDs when light level drops
3. **Data logger** - Record light levels over 24 hours
4. **Color mixer** - Use 3 LDRs to control RGB LED colors
5. **Shadow detector** - Trigger actions when someone blocks the light
6. **Plant monitor** - Alert when plants aren't getting enough light

## 🔧 Bill of Materials

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino UNO R4 WiFi | 1 | Or any Arduino UNO |
| Flying Fish LDR Module | 1 | Available on Amazon, eBay, AliExpress |
| Jumper Wires | 4-5 | Male-to-female or male-to-male |
| USB Cable | 1 | For programming and power |

**Optional:**
- External LED (if not using pin 13)
- 220Ω resistor (for external LED)
- Breadboard (for prototyping)

---

**Let there be light (sensing)! 💡**
