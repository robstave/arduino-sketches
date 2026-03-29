# One Servo - Basic Sweep

## 🎯 What This Project Does

This sketch makes a single servo motor sweep back and forth smoothly between 0° and 180°, taking 3 seconds for each direction. It's the foundation for understanding servo control.

## 🔌 Hardware Required

- **Arduino UNO** (any model)
- **Hobby servo motor** (SG90, MG90S, or similar)
- **Jumper wires**

### Wiring

| Servo Wire | Arduino Pin |
|------------|-------------|
| Red (Power) | 5V |
| Brown/Black (Ground) | GND |
| Orange/Yellow (Signal) | Pin 9 |

## 🎮 How It Works

### The Sweep Motion

The servo moves in small steps from 0° to 180°, then back to 0°, repeating forever:

1. **Sweep right:** 0° → 180° over 3 seconds
2. **Sweep left:** 180° → 0° over 3 seconds
3. **Repeat**

### Timing and Steps

The code uses a clever system to create smooth motion:

```cpp
const int SWEEP_TIME_MS = 3000;  // 3 seconds total
const int STEP_DELAY = 15;       // 15ms between each step
const int STEPS = SWEEP_TIME_MS / STEP_DELAY;  // = 200 steps
```

**How it calculates:**
- 3000ms ÷ 15ms = 200 steps
- Each step moves the servo 180° ÷ 200 = 0.9° per step
- Result: Smooth sweep taking exactly 3 seconds

### The map() Function

```cpp
int pos = map(i, 0, STEPS, 0, 180);
```

This converts step number (0 to 200) into angle (0° to 180°):
- Step 0 → 0°
- Step 100 → 90°
- Step 200 → 180°

## 💡 Key Things to Tweak

### Easy Changes

1. **Change sweep speed** - Modify the sweep time:
   ```cpp
   const int SWEEP_TIME_MS = 1500;  // Faster (1.5 seconds)
   // or
   const int SWEEP_TIME_MS = 5000;  // Slower (5 seconds)
   ```

2. **Change smoothness** - Modify the step delay:
   ```cpp
   const int STEP_DELAY = 30;  // Fewer steps, jumpier motion
   // or
   const int STEP_DELAY = 5;   // More steps, smoother motion
   ```

3. **Limited range** - Don't sweep the full 180°:
   ```cpp
   int pos = map(i, 0, STEPS, 45, 135);  // Only 45° to 135°
   ```

### Intermediate Changes

4. **Pause at ends:**
   ```cpp
   // After each for loop:
   delay(1000);  // Hold position for 1 second
   ```

5. **Asymmetric speed** (fast one way, slow the other):
   ```cpp
   // Fast sweep right
   for (int i = 0; i <= STEPS; i++) {
     int pos = map(i, 0, STEPS, 0, 180);
     myservo.write(pos);
     delay(5);  // Fast!
   }
   
   // Slow sweep left
   for (int i = 0; i <= STEPS; i++) {
     int pos = map(i, 0, STEPS, 180, 0);
     myservo.write(pos);
     delay(30);  // Slow!
   }
   ```

6. **Stepped motion** (move in chunks, not smoothly):
   ```cpp
   for (int pos = 0; pos <= 180; pos += 30) {  // Increment by 30°
     myservo.write(pos);
     delay(500);  // Pause at each position
   }
   ```

### Advanced Challenges

7. **Oscillate** (faster back-and-forth around center):
   ```cpp
   for (int pos = 60; pos <= 120; pos++) {
     myservo.write(pos);
     delay(10);
   }
   for (int pos = 120; pos >= 60; pos--) {
     myservo.write(pos);
     delay(10);
   }
   ```

8. **Sine wave** (natural easing in/out):
   ```cpp
   #include <math.h>
   for (int i = 0; i <= STEPS; i++) {
     float angle = sin(i * PI / STEPS) * 90 + 90;  // 0° to 180° sine curve
     myservo.write(angle);
     delay(STEP_DELAY);
   }
   ```

9. **Random positions:**
   ```cpp
   void loop() {
     int randomPos = random(0, 181);  // Random angle 0-180
     myservo.write(randomPos);
     delay(1000);  // Hold for 1 second
   }
   ```

## 🎓 What You're Learning

- **Servo library basics** - `attach()`, `write()`
- **The map() function** - Converting ranges
- **Timing control** - Creating precise timed motions
- **Loop structures** - Building smooth animations with for-loops
- **Constants** - Using `const` to make code more readable and tweakable

## 🐛 Debugging Tips

**Servo doesn't move at all:**
- Check wiring (especially signal wire on pin 9)
- Verify power connections (5V and GND)
- Try a different servo (could be damaged)
- Add `Serial.println(pos)` to verify code is running

**Servo moves but jerky/stuttering:**
- Increase STEP_DELAY (try 20 or 30)
- Check power supply (might need external power)
- Verify servo isn't mechanically stuck

**Servo doesn't reach full range:**
- Some servos don't actually do 0-180° (might be 10-170°)
- Adjust the map range: `map(i, 0, STEPS, 10, 170)`
- Check for physical obstructions

**Arduino resets when servo moves:**
- Servo drawing too much current from 5V pin
- Use external power supply (4× AA batteries)
- Connect battery GND to Arduino GND

## 🔗 Next Steps

Once you've mastered one servo:
- Try [two_servo](../two_servo/README.md) - Control two servos together
- Build a robot arm or pan/tilt camera mount
- Add sensor input to control servo position

---

**Sweep the competition! 🔧**
