# Starfield Animation Series

## Overview

This folder contains three progressive sketches that create a 3D starfield effect on the Arduino UNO R4's LED matrix. You'll build from a simple "flying through space" animation to an interactive spaceship simulator with joystick control and laser cannons!

## The Three-Sketch Journey

### 1. [starfield1](starfield1/) - The Basic Star Field

**What it does:** Stars appear in the center and fly outward, creating the classic "warp speed" effect.

**What you'll learn:**
- How 3D graphics work on a 2D screen
- The magic of "divide by Z" (objects far away look smaller)
- Working with arrays of moving objects

**Key things to tweak:**
- `speed` - Make it faster or slower (try 0.05 to 0.3)
- `NUM_STARS` - More stars = busier field (try 5 to 25)
- The `1.5` divisor in the projection - Controls field of view (smaller = zoomed in, larger = wide angle)

### 2. [starfield2](starfield2/) - Add Joystick Steering

**What it does:** Everything from starfield1, PLUS you can steer with a joystick! Move the joystick to "fly" left, right, up, or down through the star field.

**Hardware needed:**
- Analog joystick connected to A0 (X-axis) and A1 (Y-axis)

**What you'll learn:**
- Reading analog joystick input
- Mapping joystick values to movement
- How camera movement works in 3D space

**Key things to tweak:**
- The `/4000.0` divisor in `turnX` and `turnY` - Controls turning sensitivity (smaller = faster turns)
- Try reversing the joystick direction by swapping signs

### 3. [starfield3](starfield3/) - Add Laser Cannons!

**What it does:** Full spaceship simulator! Steer with the joystick and press the button to fire dual laser cannons.

**Hardware needed:**
- Analog joystick with button, connected to A0 (X), A1 (Y), A2 (button)

**What you'll learn:**
- Button input and debouncing
- Managing multiple moving objects (stars AND lasers)
- Creating "weapons" that travel in 3D space

**Key things to tweak:**
- `MAX_LASERS` - How many lasers can be on screen at once
- `speed * 3.0` in laser update - How fast lasers travel (try 2.0 to 5.0)
- Cannon positions (`x = -3.0` and `x = 3.0`) - Make them wider or narrower
- Laser starting position (`z = 1.0`) - Spawn closer or farther

## How the "Magic" Works (Don't Worry About the Math!)

The core trick is called **perspective projection**. Here's the simple version:

**The Problem:** We have stars in 3D space (X, Y, Z coordinates), but our screen is flat (only rows and columns).

**The Solution:** Things far away (big Z) should look small and near the center. Things close (small Z) should look big and near the edges.

**The Formula:** We divide the X and Y positions by Z, then add them to the center of the screen.

```cpp
screenX = (starX / starZ) * 1.5 + 6;  // 6 is center of 12 columns
screenY = (starY / starZ) * 1.5 + 4;  // 4 is center of 8 rows
```

**Why it works:** When Z is big (star is far), the division makes a tiny number → pixel near center. When Z is small (star is close), the division makes a big number → pixel near edge.

That's it! You don't need to understand *why* dividing by Z creates perspective - just know that **it does**, and now you can experiment with it!

## Exploration Ideas

The best way to learn is by **changing things and seeing what happens**:

1. **Start simple:** Change `speed` from 0.15 to 0.3. What happens? Now try 0.05.

2. **More stars:** Change `NUM_STARS` from 15 to 5, then to 30. How does it feel?

3. **Field of view:** In the projection formula, change `1.5` to `1.0` or `2.0`. Bigger number = wider view (more zoomed out).

4. **Star spawn range:** In `resetStar()`, the X range is `-10.0 to 10.0`. Try `-20.0 to 20.0` for wider spawning, or `-5.0 to 5.0` for a tighter "tunnel."

5. **Joystick sensitivity:** In starfield2/3, the `/4000.0` controls how responsive steering is. Try `/2000.0` (more sensitive) or `/8000.0` (less sensitive).

6. **Laser speed:** In starfield3, lasers travel at `speed * 3.0`. Try `speed * 5.0` for super fast, or `speed * 1.5` for slower bolts.

7. **Weapon placement:** Change the laser cannon X positions from `-3.0` and `3.0` to something else. What if they were both at `0.0` (center fire)?

## What You're Actually Learning

Even though we're not diving deep into the math, you're learning **real game development concepts**:

- **3D to 2D projection** - The foundation of every 3D game and movie
- **Frame-based animation** - How to create smooth motion
- **Object pooling** - Reusing stars/lasers instead of creating new ones
- **Input mapping** - Turning sensor values into useful game controls
- **State management** - Tracking multiple moving objects

These are the same techniques used in professional games, just simplified for a tiny LED matrix!

## 🔗 Resources

- [Arduino UNO R4 WiFi Documentation](https://docs.arduino.cc/hardware/uno-r4-wifi)
- [Arduino LED Matrix Library](https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix)
- For the math-curious: see the individual starfield1 and starfield2 READMEs for detailed projection formulas

---

**Now pick a sketch, upload it, and start tweaking! 🌟**
