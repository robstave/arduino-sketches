# Starfield3 - Spaceship Simulator with Laser Cannons

## What This Project Does

This is the complete starfield experience! You control a spaceship flying through space with a joystick, and you can fire dual laser cannons by pressing the joystick button. It combines everything from starfield1 and starfield2 with weapon systems.

## Hardware Required

- **Arduino UNO R4 WiFi** (the board with the built-in 8x12 LED matrix)
- **Analog Joystick Module** with button
  - VCC → 5V
  - GND → GND
  - VRx → A0 (X-axis: left/right steering)
  - VRy → A1 (Y-axis: up/down steering)
  - SW → A2 (Fire button)

![Joystick Wiring Diagram](../../assets/joystick-wiring.png)

## Controls

- **Move joystick** - Steer your ship (stars and lasers move together)
- **Press button** - Fire dual laser cannons from wing positions

## How Laser Fire Works

When you press the joystick button, the code spawns **two laser bolts** simultaneously:

```cpp
// Left cannon
lasers[0].x = -3.0;   // 3 units to the left
lasers[0].y = 1.5;    // Slightly below center
lasers[0].z = 1.0;    // Close to the camera

// Right cannon  
lasers[1].x = 3.0;    // 3 units to the right
lasers[1].y = 1.5;    // Slightly below center
lasers[1].z = 1.0;    // Close to the camera
```

### Laser Movement

Lasers travel **away from you** (Z increases) at **3× the star speed**:

```cpp
lasers[i].z += speed * 3.0;  // Move away FAST
```

This makes them shoot forward rapidly while stars flow toward you slowly - creating the perfect spaceship combat feel!

### Laser Lifecycle

1. **Spawn** - Button pressed → two lasers created at wing positions
2. **Travel** - Lasers move forward (Z increases) each frame
3. **Display** - Same 3D-to-2D projection as stars
4. **Despawn** - When `z > 15.0`, laser is marked inactive and can be reused

## Key Things to Tweak

### Easy Changes

1. **Laser speed** (line ~113):
   ```cpp
   lasers[i].z += speed * 3.0;  // Try 2.0 to 5.0
   ```
   - Bigger number = faster lasers
   - Smaller number = slower, more visible lasers

2. **Maximum lasers** (line ~26):
   ```cpp
   const int MAX_LASERS = 4;  // Try 2 to 8
   ```
   - More lasers = can fire faster (but more screen clutter)

3. **Cannon positions** (lines ~99-100, ~104-105):
   ```cpp
   lasers[idx1].x = -3.0;  // Left cannon (try -2.0 to -5.0)
   lasers[idx2].x = 3.0;   // Right cannon (try 2.0 to 5.0)
   ```
   - Bigger numbers = wider spread
   - Both at 0.0 = center-fire cannon

4. **Laser spawn distance** (lines ~101, ~106):
   ```cpp
   lasers[idx].z = 1.0;  // Try 0.5 to 2.0
   ```
   - Smaller = spawns closer to screen (appears bigger)
   - Larger = spawns farther away (appears smaller)

### Intermediate Changes

5. **Vertical cannon offset** (lines ~100, ~105):
   ```cpp
   lasers[idx].y = 1.5;  // Try 0.0 to 3.0
   ```
   - Change where cannons are vertically (1.5 is slightly below center)

6. **Laser lifespan** (line ~118):
   ```cpp
   if (lasers[i].z > 15.0) {  // Try 10.0 to 20.0
   ```
   - Bigger number = lasers visible longer
   - Smaller number = lasers disappear sooner

7. **Button debounce delay** - None! Uses state tracking instead:
   ```cpp
   if (buttonState == LOW && lastButtonState == HIGH)
   ```
   This only fires when button *transitions* from released to pressed

### Advanced Challenges

8. **Single cannon mode:** Change `fireLaser()` to only spawn one laser at center:
   ```cpp
   if (slotsFound >= 1) {
     lasers[indices[0]].x = 0.0;  // Center fire
   ```

9. **Rapid fire:** Remove the "slotsFound == 2" check to fire as fast as you click (up to MAX_LASERS limit)

10. **Alternating cannons:** Make left and right cannons fire alternately instead of together

11. **Different laser colors:** Add a trail effect by keeping lasers visible for a few frames after they pass each pixel

## 🎓 What You're Learning

- **Button state detection** - Tracking button transitions (not just "is it pressed?")
- **Object pooling** - Reusing laser slots instead of creating/destroying objects
- **Projectile physics** - Making objects travel in a specific direction at a speed
- **Collision-free firing** - Finding available slots before spawning new lasers
- **Independent object movement** - Lasers and stars move at different speeds

## 🐛 Debugging Tips

**Lasers not appearing?**
- Check `MAX_LASERS` - you might have all slots filled
- Watch the Serial Monitor to see if button presses are detected
- Make sure `speed * 3.0` isn't so fast that lasers jump off-screen in one frame

**Lasers going the wrong direction?**
- If they come toward you instead of away, change `+=` to `-=` in laser update

**Button not working?**
- Verify pin A2 is connected to the joystick SW pin
- Check that `INPUT_PULLUP` is set in setup
- Remember: button reads LOW when pressed, HIGH when released

## 🔗 Related Projects

- [starfield1](../starfield1/readme.md) - The basic star field (no joystick)
- [starfield2](../starfield2/readme.md) - Joystick steering (no lasers)
- [Parent starfield README](../readme.md) - Overview of all three sketches

---

**Fire away! 🎯✨**
