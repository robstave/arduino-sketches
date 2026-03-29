# Traffic Light Control Projects

Learn to program traffic light sequences, from simple blinking to complex multi-intersection timing. Progress from flat code to clean, function-based programs.

## 🚦 About Traffic Lights

Traffic lights are perfect for learning:
- Sequential logic (one state after another)
- Timing control (how long each light stays on)
- Functions and code organization
- State machines (managing complex behaviors)

## 🛠️ Hardware Options

### Option 1: Dedicated Traffic Light Module

**Recommended:** [Arduino Mini Traffic Light Display Module](https://www.amazon.com/Traffic-Display-Module-Arduino-Mini-Traffic/dp/B07SZMRSDN/)

This pre-wired module has LEDs and resistors built-in - just connect to Arduino pins!

### Option 2: Individual LEDs + Resistors

Build your own with:
- 3× Red LEDs (or 6 for two intersections)
- 3× Yellow LEDs (or 6 for two)
- 3× Green LEDs (or 6 for two)
- 6× 220Ω resistors (or 12 for two intersections)
- Breadboard and jumper wires

Both options work identically in code!

## 📊 Project Overview

| Sketch | Readme | Description | Wiring |
|--------|--------|-------------|--------|
| traffic-one | [traffic-one/README.md](traffic-one/README.md) | Flat code, simple sequence | 3 LEDs (pins 11, 12, 13) |
| traffic_one_function | [traffic_one_function/README.md](traffic_one_function/README.md) | Introduces functions + enum | 3 LEDs (pins 11, 12, 13) |
| traffic__two_function | [traffic__two_function/README.md](traffic__two_function/README.md) | Two intersections, coordinated | 6 LEDs (pins 5,6,7 + 11,12,13) |
| traffic__two_function_led | [traffic__two_function_led/README.md](traffic__two_function_led/README.md) | Same as above, for LED module | LED module wiring |

## 🔌 Wiring Guide

### Single Intersection (traffic-one, traffic_one_function)

| LED Color | Arduino Pin | Notes |
|-----------|-------------|-------|
| Red | 13 | Through 220Ω resistor |
| Yellow | 12 | Through 220Ω resistor |
| Green | 11 | Through 220Ω resistor |

Each LED also connects to GND.

### Two Intersections (traffic__two_function)

**Intersection 1:**
| LED Color | Arduino Pin |
|-----------|-------------|
| Red 1 | 13 |
| Yellow 1 | 12 |
| Green 1 | 11 |

**Intersection 2:**
| LED Color | Arduino Pin |
|-----------|-------------|
| Red 2 | 7 |
| Yellow 2 | 6 |
| Green 2 | 5 |

All LEDs through 220Ω resistors to GND.

## 🎓 Learning Progression

### 1. [traffic-one](traffic-one/) - The Foundation

**Pure sequential code** - Everything in `loop()`, easy to read top-to-bottom:
```cpp
void loop() {
  digitalWrite(redLight1, HIGH);
  delay(899);
  digitalWrite(greenLight1, HIGH);
  delay(899);
  // ... etc
}
```

**What you'll learn:**
- Digital output basics
- Timing with delay()
- Traffic light sequences

**Good for:** Understanding the basic logic flow

### 2. [traffic_one_function](traffic_one_function/) - Functions and Enums

**Introduces organization** - Same behavior, cleaner code:
```cpp
enum TrafficLight { RED, YELLOW, GREEN };

void setLight1(TrafficLight light) {
  // Turn off all, turn on one
}

void loop() {
  setLight1(RED);
  delay(899);
  // ... etc
}
```

**What you'll learn:**
- Functions for code reuse
- Enums for readable state names
- Switch statements

**Note:** This sketch has a bug! The `switch` statement has misplaced code. Good for learning debugging!

### 3. [traffic__two_function](traffic__two_function/) - Multiple Intersections

**Real-world complexity** - Coordinated traffic control:
```cpp
void setLights(TrafficLight light1, TrafficLight light2) {
  // Control both intersections
}

void loop() {
  setLights(RED, GREEN);    // Intersection 1 red, 2 green
  setLights(GREEN, RED);    // Intersection 1 green, 2 red
  // ... with yellow transitions
}
```

**What you'll learn:**
- Multi-output coordination
- Intersection timing logic
- Function parameters

**Realistic behavior:** Includes transition yellows and all-red safety periods

### 4. [traffic__two_function_led](traffic__two_function_led/) - Hardware Variant

**Same logic, different wiring** - Shows that code can work with different hardware setups.

## 🎯 Traffic Light Logic

### Basic Sequence (Single Intersection)

1. **Red** (stop) - 899ms
2. **Green** (go) - 899ms  
3. **Yellow** (caution) - 300ms
4. **Repeat**

### Two-Intersection Sequence

1. **Light 1: Red | Light 2: Green** (899ms) - East-west flows
2. **Light 1: Red | Light 2: Yellow** (300ms) - East-west prepares to stop
3. **Light 1: Red | Light 2: Red** (300ms) - All-red safety period
4. **Light 1: Green | Light 2: Red** (899ms) - North-south flows
5. **Light 1: Yellow | Light 2: Red** (300ms) - North-south prepares to stop
6. **Light 1: Red | Light 2: Red** (300ms) - All-red safety period
7. **Repeat**

The **all-red period** is important in real intersections - it gives time for the intersection to clear before the other direction gets a green light.

## 💡 Things to Experiment With

1. **Timing:** Change the delay values - what feels more realistic?
2. **Sequence:** What if yellow comes BEFORE green (like some countries)?
3. **Pedestrian crossing:** Add a 4th LED for walk signal
4. **Turn arrows:** Add left/right turn signals
5. **Sensor input:** Use a button to simulate car detection (green on demand)
6. **Time of day:** Longer greens during rush hour (use `millis()` for time)

## 🔧 Bill of Materials

### For LED Module

| Component | Quantity |
|-----------|----------|
| Arduino UNO | 1 |
| Traffic Light LED Module | 1 or 2 |
| Jumper Wires | 6-12 |

### For DIY Build

| Component | Quantity (1 light) | Quantity (2 lights) |
|-----------|-------------------|---------------------|
| Arduino UNO | 1 | 1 |
| Red LED (5mm) | 1 | 2 |
| Yellow LED (5mm) | 1 | 2 |
| Green LED (5mm) | 1 | 2 |
| 220Ω Resistor | 3 | 6 |
| Breadboard | 1 | 1 |
| Jumper Wires | ~10 | ~15 |

## 🔗 Resources

- [Digital Output Tutorial (Arduino)](https://www.arduino.cc/en/Tutorial/Foundations/DigitalPins)
- [Traffic Light Timing Standards (MUTCD)](https://mutcd.fhwa.dot.gov/) - Real-world specifications
- [Enum Tutorial (Arduino)](https://www.arduino.cc/reference/en/language/structure/compound-operators/enum/)

---

**Stop, look, and code! 🚦**
