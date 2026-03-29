# Eye1 - Interactive Eyeball Tracker

## 🎯 What This Project Does

This sketch creates a realistic eyeball animation on the Arduino UNO R4's LED matrix that responds to joystick input in real-time. Move the joystick to make the eye look around, and press the button to make it blink!

## 🛠️ Hardware Setup

Follow the main [eyeball folder README](../readme.md) for wiring instructions connecting your joystick to pins A0 (X), A1 (Y), and A2 (button).

## 🎨 How It Works

### The Eye Structure

The eye is drawn in two parts:
1. **Sclera** (white of the eye) - An oval shape that fills most of the display
2. **Pupil** (dark center) - A 2x2 pixel black square that moves around

### Joystick Control

- **Move joystick left/right**: Pupil moves horizontally (X-axis: positions 2-8)
- **Move joystick up/down**: Pupil moves vertically (Y-axis: positions 1-5)
- **Press button**: Triggers a smooth blink animation

### The Blink Animation

When you press the joystick button, the eye:
1. Gradually closes (eyelid moves in from top and bottom)
2. Stays closed briefly
3. Gradually opens back up

The "openness" parameter controls how much of the eye is visible, creating smooth eyelid movement.

## 🧮 Key Programming Concepts

### Analog Input Mapping

```cpp
int pupilX = map(joyX, 0, 1023, 2, 8);
```
The `map()` function converts joystick values (0-1023) to pupil positions (2-8), keeping the pupil within the eye boundaries.

### Constrain Function

```cpp
pupilX = constrain(pupilX, 2, 8);
```
Ensures values stay within safe bounds, preventing the pupil from drawing outside the screen.

### Parametric Drawing

The `drawEye()` function uses an "openness" parameter (0.0 to 1.0) to control the eyelid position:
- **1.0** = Fully open
- **0.5** = Half open
- **0.0** = Completely closed

### Button Debouncing

```cpp
delay(200); 
while(digitalRead(PIN_BTN) == LOW);
```
Waits for the button to be released before continuing, preventing multiple blinks from a single press.

## 💡 Try These Modifications

### Beginner Level
1. Change the blink speed by modifying the delay values
2. Make the pupil larger or smaller (change from 2x2 to 3x3 or 1x1)
3. Adjust the eye's range of motion by changing the map() target values

### Intermediate Level
1. Add automatic blinking every few seconds using `millis()`
2. Make the pupil move more slowly (smooth following rather than instant)
3. Invert the joystick directions if they feel backward
4. Add random small eye movements for a "living" effect

### Advanced Level
1. Create two eyes that move together
2. Add an iris (ring around the pupil)
3. Make the pupil change size based on light sensor input
4. Create different eye expressions (angry, happy, sleepy)
5. Add eyebrow animation above the eye
6. Make the eyes "watch" something moving across the screen

## 🔍 Understanding the Math

### Oval Shape Creation

The eye uses boundary conditions to create an oval:
```cpp
// Corners are trimmed for rounded edges
if ((y == 0 || y == 7) && (x < 2 || x > 9)) 
  isSclera = false;
```

### Eyelid Position

The vertical center of the display is 3.5. The code calculates how far each row can be from center:
```cpp
float maxDist = 4.0 * openness;
if (abs(y - 3.5) > maxDist) 
  isSclera = false;
```
When openness = 0.5, only rows within 2 pixels of center are visible (half-closed eye).

## 📊 Performance Notes

- **Frame Rate**: Updates approximately 30 times per second (30fps)
- **Blink Duration**: About 0.5 seconds total
- **Joystick Sensitivity**: Full range mapped to limited screen space

## 🔗 Related Resources

- [Parent Folder Documentation](../readme.md)
- [Arduino Joystick Tutorial](https://arduinogetstarted.com/tutorials/arduino-joystick)

---

**Make it blink! 👁️✨**
