# Traffic__Two_Function_LED - LED Module Version

## 🎯 What This Project Does

This is the **exact same logic** as [traffic__two_function](../traffic__two_function/README.md), but wired for a dedicated LED traffic light module instead of individual LEDs on a breadboard.

## 🔌 Hardware Required

- **Arduino UNO** (any model)
- **Traffic Light LED Module** - [Amazon Link](https://www.amazon.com/Traffic-Display-Module-Arduino-Mini-Traffic/dp/B07SZMRSDN/)
- **Jumper wires**

### Module Wiring

The LED module has pre-wired LEDs and resistors. Just connect:

| Module Pin | Arduino Pin | Signal |
|------------|-------------|--------|
| R1 | 13 | Red Light 1 |
| Y1 | 12 | Yellow Light 1 |
| G1 | 11 | Green Light 1 |
| R2 | 7 | Red Light 2 |
| Y2 | 6 | Yellow Light 2 |
| G2 | 5 | Green Light 2 |
| GND | GND | Common ground |
| VCC (if present) | 5V | Power (some modules) |

**Note:** Some modules are "common cathode" (share GND) while others are "common anode" (share VCC). Check your module's documentation!

## 📊 How It Works

**Exactly the same as traffic__two_function!** The code is identical because Arduino doesn't care whether you're controlling individual LEDs or a fancy module - it's all just turning pins HIGH and LOW.

### The Sequence

Same realistic intersection timing:
1. Light 1 red, Light 2 green → 899ms
2. Light 1 red, Light 2 yellow → 300ms
3. Both red (safety period) → 300ms
4. Light 1 green, Light 2 red → 899ms
5. Light 1 yellow, Light 2 red → 300ms
6. Both red (safety period) → 300ms
7. Repeat

For detailed explanation, see [traffic__two_function README](../traffic__two_function/README.md).

## 💡 Why This Separate Version Exists

This sketch exists to show that **software and hardware are separate concerns**:
- Same code
- Same logic
- Different physical implementation

**What this teaches:**
- Code is portable (works with different hardware)
- Abstraction (Arduino pins work the same regardless of what's connected)
- Hardware flexibility (swap components without changing code)

## 🔧 Module-Specific Notes

### Advantages of the Module

- **Cleaner setup** - No breadboard, resistors, or individual LEDs
- **More realistic** - Looks like an actual traffic light
- **Compact** - Takes up less space
- **Durable** - Solderedconnections vs. breadboard jumpers

### Potential Issues

**Common Anode vs. Common Cathode:**

If your module shares VCC (common anode), the logic is INVERTED:
- `HIGH` turns LED OFF
- `LOW` turns LED ON

**Fix:** Reverse all digitalWrite calls:
```cpp
digitalWrite(redLight1, LOW);  // Turn ON (for common anode)
// instead of HIGH
```

Or just swap your wiring: connect module's "GND" to Arduino 5V and "VCC" to GND (if module can handle it).

## 💡 All Modifications Are the Same!

Every tweak from traffic__two_function works here:
- Rush hour timing
- Pedestrian walk signals
- Sensor-triggered lights
- Emergency flash modes
- Time-of-day adaptations

Just use the same code - the module doesn't know the difference!

## 🎓 What You're Learning

- **Hardware abstraction** - Same code, different hardware
- **Pin mapping** - How software connects to physical world
- **Modularity** - Components can be swapped without code changes
- **Real-world applicability** - Traffic light modules are used in RC cars, model trains, robotics education

## 🔗 Next Steps

- Try all the modifications from [traffic__two_function](../traffic__two_function/README.md)
- Add sensors for interactive intersection
- Connect to a model city or train layout
- Build a 4-way intersection control system

---

**Plug and play! 🚦⚡**
