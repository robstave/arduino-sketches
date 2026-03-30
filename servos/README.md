# Servo Motor Control Projects

Learn how to control servo motors with Arduino - from simple sweeps to coordinated multi-servo movements.

## About Servo Motors

Servo motors are special motors that can move to a specific angle (0° to 180°) and hold that position. They're perfect for:
- Robot arms and grippers
- Camera pan/tilt mechanisms
- RC car steering
- Animatronics and moving displays

## Project Overview

| Sketch | Readme | Description | Servos Needed |
|--------|--------|-------------|---------------|
| one_servo | [one_servo/README.md](one_servo/README.md) | Single servo sweep (0° ↔ 180°) | 1 |
| two_servo | [two_servo/README.md](two_servo/README.md) | Two servos sweeping in sync | 2 |

## Servo Wiring

### Standard 3-Wire Servo Connection

| Servo Wire | Arduino Pin | Description |
|------------|-------------|-------------|
| Red / VCC | 5V | Power (4.8-6V) |
| Brown / Black / GND | GND | Ground |
| Orange / Yellow / Signal | 9 or 10 | PWM control signal |

**Important Notes:**
- **one_servo** uses pin 9
- **two_servo** uses pins 9 AND 10
- Most small servos can be powered from Arduino's 5V pin
- **Larger servos** (high-torque, metal gear) may need an external power supply

### When to Use External Power

If you have multiple servos or high-torque servos:
1. Use a separate 5-6V power supply (like a 4× AA battery pack)
2. Connect the power supply GND to Arduino GND (common ground)
3. Connect servo red wires to external power, NOT Arduino 5V
4. Still connect servo signal wires to Arduino pins 9/10

## How Servo Control Works

### PWM (Pulse Width Modulation)

Servos are controlled by sending pulses of specific widths:
- **1.0 ms pulse** = 0° (fully left)
- **1.5 ms pulse** = 90° (center)
- **2.0 ms pulse** = 180° (fully right)

The Arduino Servo library handles this automatically - you just call:
```cpp
myservo.write(90);  // Move to 90 degrees
```

### Smooth Movement

Our sketches don't jump directly from 0° to 180°. Instead, they move in small steps:

```cpp
for (int pos = 0; pos <= 180; pos++) {
  myservo.write(pos);
  delay(15);  // 15ms between steps
}
```

This creates smooth, realistic motion instead of jerky jumps.

## Learning Progression

### 1. [one_servo](one_servo/) - Basic Control

Master the fundamentals:
- Attaching a servo to a pin
- Moving to specific angles
- Creating sweep animations
- Timing and speed control

### 2. [two_servo](two_servo/) - Coordination

Learn multi-servo techniques:
- Controlling multiple servos
- Synchronized movement
- Independent positioning
- Creating complex motions

## Common Uses for Servos

- **Robotics** - Joints, grippers, arms
- **RC vehicles** - Steering, camera gimbals
- **Home automation** - Blinds, locks, pet feeders
- **Art projects** - Kinetic sculptures, interactive displays
- **Instruments** - Automated percussion, chord changers

## Bill of Materials

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino UNO R4 WiFi | 1 | Or any Arduino board |
| Hobby Servo Motor (e.g., SG90) | 1-2 | 9g micro servo or similar |
| Jumper Wires | 3-6 | Male-to-male or male-to-female |
| External Power Supply (optional) | 1 | 4× AA battery holder or 5V adapter |

**Recommended Servo:** SG90 or MG90S (cheap, common, easy to find)

## 🐛 Common Issues

**Servo not moving:**
- Check wiring: Signal to pin 9/10, power to 5V, ground to GND
- Verify servo is attached in code: `myservo.attach(9)`
- Try a different servo (could be broken)

**Servo jittering/shaking:**
- Not enough power - use external power supply
- Loose wiring - check connections
- Interference - keep servo wires away from other electronics

**Servo moves but not to correct angles:**
- Some servos have limited range (not quite 0-180°)
- Calibration might be needed: trim the range in code
- Physical obstruction preventing movement

**Arduino resets when servo moves:**
- Servo drawing too much current - MUST use external power
- Never power multiple or large servos from Arduino 5V pin

## 🔗 Resources

- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/)
- [Servo Motor Basics (SparkFun)](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial)
- [PWM Explained (Arduino)](https://www.arduino.cc/en/Tutorial/Foundations/PWM)

---

**Get moving! 🔧**
