# Two Servo - Synchronized Movement

## What This Project Does

This sketch controls TWO servo motors, making them sweep back and forth in perfect synchronization. Both servos move together at the same speed, creating coordinated motion.

## Hardware Required

- **Arduino UNO** (any model)
- **2× Hobby servo motors** (SG90, MG90S, or similar)
- **Jumper wires**
- **External power supply** (recommended for 2+ servos)

### Wiring

| Servo 1 | Servo 2 | Arduino Pin |
|---------|---------|-------------|
| Red | Red | 5V (or external power) |
| Brown | Brown | GND (common ground) |
| Signal | - | Pin 9 |
| - | Signal | Pin 10 |

**Power Warning:** Two servos can draw significant current. If servos jitter, twitch, or Arduino resets, you MUST use external power (4× AA battery pack connected to servo power wires, with GND connected to Arduino GND).

## How It Works

### Two Servo Objects

```cpp
Servo myservo1;  // Controls servo on pin 9
Servo myservo2;  // Controls servo on pin 10
```

Each servo gets its own object, allowing independent control even though they move together in this sketch.

### Synchronized Movement

Both servos receive the same angle at the same time:

```cpp
myservo1.write(pos);
myservo2.write(pos);
```

This creates perfectly synchronized sweeps - like two windshield wipers or robot arms moving in unison.

## Key Things to Tweak

### Easy Changes

1. **Change sweep speed** (same as one_servo):
   ```cpp
   const int SWEEP_TIME_MS = 2000;  // Faster (2 seconds)
   ```

2. **Opposite directions** - Make one servo sweep backwards:
   ```cpp
   myservo1.write(pos);
   myservo2.write(180 - pos);  // Inverse angle
   ```

3. **Different ranges** - Give each servo a different movement range:
   ```cpp
   int pos1 = map(i, 0, STEPS, 0, 180);    // Full range
   int pos2 = map(i, 0, STEPS, 45, 135);   // Limited range
   myservo1.write(pos1);
   myservo2.write(pos2);
   ```

### Intermediate Changes

4. **Offset timing** - One servo lags behind the other:
   ```cpp
   for (int i = 0; i <= STEPS; i++) {
     int pos1 = map(i, 0, STEPS, 0, 180);
     int pos2 = map(constrain(i-20, 0, STEPS), 0, STEPS, 0, 180);  // 20 steps behind
     myservo1.write(pos1);
     myservo2.write(pos2);
     delay(STEP_DELAY);
   }
   ```

5. **Wave motion** - Create a ripple effect:
   ```cpp
   for (int i = 0; i <= STEPS * 2; i++) {
     int pos1 = map(i, 0, STEPS * 2, 0, 180);
     int pos2 = map((i + STEPS) % (STEPS * 2), 0, STEPS * 2, 0, 180);
     myservo1.write(pos1);
     myservo2.write(pos2);
     delay(STEP_DELAY / 2);
   }
   ```

6. **Independent speeds** - One servo moves faster:
   ```cpp
   void loop() {
     for (int i = 0; i <= STEPS; i++) {
       myservo1.write(map(i, 0, STEPS, 0, 180));
       if (i % 2 == 0) {  // Only update servo2 every other step
         myservo2.write(map(i/2, 0, STEPS/2, 0, 180));
       }
       delay(STEP_DELAY);
     }
   }
   ```

### Advanced Challenges

7. **Scissor motion** - Servos close together then spread apart:
   ```cpp
   for (int i = 0; i <= STEPS; i++) {
     int center = 90;
     int spread = map(i, 0, STEPS, 0, 45);  // 0° to 45° from center
     myservo1.write(center - spread);  // 90° down to 45°
     myservo2.write(center + spread);  // 90° up to 135°
     delay(STEP_DELAY);
   }
   ```

8. **Random walk** - Each servo wanders independently:
   ```cpp
   int pos1 = 90, pos2 = 90;
   void loop() {
     pos1 += random(-5, 6);  // Random step -5 to +5
     pos2 += random(-5, 6);
     pos1 = constrain(pos1, 0, 180);
     pos2 = constrain(pos2, 0, 180);
     myservo1.write(pos1);
     myservo2.write(pos2);
     delay(50);
   }
   ```

9. **Interactive pan/tilt** - Use joystick or potentiometers to control each servo independently

10. **Choreographed sequence** - Create a dance routine with specific movements:
    ```cpp
    void choreography() {
      // Move 1: Both sweep right
      sweepBoth(0, 180, 1000);
      delay(500);
      
      // Move 2: Opposite directions
      sweepOpposite(0, 180, 1500);
      delay(500);
      
      // Move 3: Rapid oscillation
      oscillate(10, 500);
    }
    ```

## 🎓 What You're Learning

- **Multiple object management** - Creating and controlling multiple servo instances
- **Synchronized motion** - Coordinating multiple outputs
- **Independent vs. coupled control** - When to move together, when separately
- **Mathematical relationships** - Creating inverse, offset, and wave motions

## 🛠️ Project Ideas

With two servos, you can build:

1. **Pan/Tilt Camera Mount** - One servo pans (left/right), one tilts (up/down)
2. **Robot Gripper** - Two servos as claw fingers
3. **Animatronic Eyes** - Two servos control eye positions
4. **Dual-Axis Solar Tracker** - Track the sun in two dimensions
5. **Drawing Robot** - X and Y axis control for pen plotter
6. **Kinetic Sculpture** - Coordinated artistic movements

## 🐛 Debugging Tips

**Both servos jitter or shake:**
- Definitely a power problem - use external battery pack
- 4× AA batteries (6V) work great for most servos
- Connect battery (-) to Arduino GND

**One servo works, other doesn't:**
- Check pin numbers in code (should be 9 and 10)
- Verify wiring (signal wire to correct pin)
- Try swapping servos to isolate if it's code or hardware

**Servos move but not in sync:**
- This is correct! The code runs line-by-line, so tiny delays exist
- For true simultaneity, would need hardware PWM or servo controller board
- Current timing is close enough for most applications

**Random resets or glitches:**
- Power supply can't provide enough current
- Add capacitors (100µF) across servo power/ground
- Use regulated external power supply

## 🔗 Next Steps

Master two servos, then:
- Add more servos (Arduino can control up to ~12 on different pins)
- Add joystick control for manual positioning
- Build a robot arm or walking robot
- Explore servo controller boards for 16+ servos

---

**Double the servos, double the fun! 🔧🔧**
