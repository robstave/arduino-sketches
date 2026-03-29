# Arduino Sketches - Learning Collection

A collection of Arduino sketches designed for high school students learning physical computing with the **Arduino UNO R4 WiFi**. Projects range from simple LED control to interactive graphics, sensors, and motor control.

## 🎯 About This Repository

These sketches emphasize **hands-on exploration and cause-and-effect learning**. The goal is to:
- Upload code and see what happens
- Tweak parameters and observe the results
- Build understanding through experimentation
- Learn debugging skills with real hardware

**Target audience:** High school students with basic programming knowledge

**Hardware focus:** Arduino UNO R4 WiFi (but most sketches work on other Arduino boards)

## 📂 Project Categories

| Folder | Description | Projects |
|--------|-------------|----------|
| [ledmatrix/](ledmatrix/) | Animations and displays using the UNO R4's built-in 12×8 LED matrix | 8 projects: text display, animations, starfields, interactive eye tracking |
| [ldr/](ldr/) | Light sensor experiments with the Flying Fish LDR module | 3 projects: basic reading, debugging practice, LED visualization |
| [servos/](servos/) | Servo motor control - positioning and coordinated movement | 2 projects: single servo sweep, dual servo sync |
| [traffic-light/](traffic-light/) | Traffic light sequences from simple to complex multi-intersection timing | 4 projects: flat code, functions, two intersections, LED module |

## 🚀 Getting Started

### 1. Choose a Category

Pick a folder based on what hardware you have or what sounds interesting:
- **No extra hardware?** Start with [ledmatrix/](ledmatrix/)
- **Have a light sensor?** Try [ldr/](ldr/)
- **Have servos?** Check out [servos/](servos/)
- **Have LEDs?** Build [traffic-light/](traffic-light/) sequences

### 2. Read the Category README

Each folder has a comprehensive README explaining:
- Hardware requirements
- Project progression (beginner → advanced)
- Wiring diagrams
- Learning objectives

### 3. Pick a Project

Start with the simplest project in each category, then progress to more complex ones.

### 4. Experiment!

The real learning happens when you:
- Change delay times
- Modify ranges and thresholds
- Add features
- Break things and fix them
- Combine ideas from different projects

## 🛠️ Required Hardware

### Core Equipment

- **Arduino UNO R4 WiFi** - Required for most projects (some work on other boards)
- **USB Cable** - For programming and power
- **Computer** - With Arduino IDE installed

### Optional Components

Different projects need different parts. See each category's README for specifics:

| Component | Used In | Notes |
|-----------|---------|-------|
| Analog Joystick Module | ledmatrix (some projects), visual1 | 5-pin module with X/Y + button |
| Flying Fish LDR Module | ldr/* | Light sensor breakout board |
| Hobby Servo Motors | servos/* | SG90 or similar 9g micro servos |
| LEDs + Resistors | traffic-light/* | Or use a traffic light module |
| Jumper Wires | All projects with external hardware | Various types |
| Breadboard | Manual LED wiring | Half-size or full-size |

## 📚 Learning Philosophy

### Cause and Effect Over Theory

You don't need to understand every line of math to learn. Instead:
1. **Run the code** - See what it does
2. **Change a number** - Observe what changes
3. **Form a hypothesis** - "I think this controls speed"
4. **Test it** - Change the value and verify
5. **Learn** - Now you understand that parameter!

### Example: Starfield Speed

```cpp
float speed = 0.15;  // Try changing to 0.05 or 0.3
```

**Don't ask:** "What's the mathematical derivation of perspective projection?"

**Do ask:** "What happens if I make speed bigger? Smaller? Negative?"

### Debugging Skills

The **Serial Monitor** is your best friend:
- Watch sensor values in real-time
- Understand what your hardware is seeing
- Verify your assumptions
- Find bugs by seeing what's actually happening

See [ldr/flyingfish-debug](ldr/flyingfish-debug/) for dedicated debugging practice.

## 🎓 Skill Progression

### Beginner Skills
- Digital output (LEDs on/off)
- Timing with delay()
- Analog input (reading sensors)
- Serial Monitor debugging

**Try:** traffic-light/traffic-one, ldr/flyingfish1

### Intermediate Skills
- Functions and code organization
- Enums and constants
- Multiple output coordination
- Frame-based animation
- Input mapping

**Try:** traffic-light/traffic__two_function, ledmatrix/car-driving, servos/two_servo

### Advanced Skills
- 3D graphics projection
- State machines
- Multi-object management
- Real-time interaction
- Hardware limitations and workarounds

**Try:** ledmatrix/starfield3, ledmatrix/eyeball, ledmatrix/visual1

## 🤖 AI-Assisted Learning

Some projects (like [visual1](ledmatrix/visual1/)) were created with AI assistance. This demonstrates:
- Using AI tools to generate starting code
- Understanding hardware limitations through experimentation
- Debugging AI-generated code
- Learning from what doesn't work as expected

**Encouraged approach:**
1. Ask AI to create a sketch for an idea
2. Upload and observe what happens
3. Iterate: "This does X but I want Y - how do I fix it?"
4. Learn both from successes AND failures

## 🔗 Resources

### Arduino References
- [Arduino UNO R4 WiFi Documentation](https://docs.arduino.cc/hardware/uno-r4-wifi)
- [Arduino Language Reference](https://www.arduino.cc/reference/en/)
- [Arduino IDE Download](https://www.arduino.cc/en/software)

### Component Guides
- [Joystick Tutorial](https://arduinogetstarted.com/tutorials/arduino-joystick)
- [Flying Fish LDR Manual](https://www.instructables.com/LDR-Sensor-Module-Users-Manual-V10/)
- [Servo Motor Basics](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial)

### Learning Resources
- [Arduino Getting Started](https://www.arduino.cc/en/Guide)
- [Fritzing](https://fritzing.org/) - Circuit diagram tool
- [TinkerCAD Circuits](https://www.tinkercad.com/) - Simulate Arduino online

## 📄 License

Individual sketches may have their own licenses (noted in file headers). Most code is either public domain or MIT licensed for educational use.

## 🤝 Contributing

This is an educational repository. Contributions welcome:
- Bug fixes
- Better explanations
- Additional learning resources
- New beginner-friendly projects
- Improved comments

Keep the focus on **high school learning** and **cause-and-effect exploration**.

---

**Happy making! Build, break, learn, repeat! 🚀✨**
