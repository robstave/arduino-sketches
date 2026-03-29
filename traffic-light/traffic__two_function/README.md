# Traffic__Two_Function - Two-Intersection Control

## 🎯 What This Project Does

This sketch controls TWO traffic lights at an intersection, coordinating them so one is red while the other is green, with proper yellow transitions and safety all-red periods between changes.

## 🔌 Hardware Setup

You need 6 LEDs - see the main [traffic-light folder README](../README.md) for complete wiring:
- **Intersection 1:** Pins 13 (red), 12 (yellow), 11 (green)
- **Intersection 2:** Pins 7 (red), 6 (yellow), 5 (green)

## 📊 How It Works

### The Intersection Logic

Real traffic intersections never give both directions a green light at the same time - that would cause collisions! This sketch implements proper intersection timing:

1. **Light 1: Red | Light 2: Green** (899ms) - East-west traffic flows
2. **Light 1: Red | Light 2: Yellow** (300ms) - East-west prepares to stop
3. **Light 1: Red | Light 2: Red** (300ms) - **Safety period** - intersection clears
4. **Light 1: Green | Light 2: Red** (899ms) - North-south traffic flows
5. **Light 1: Yellow | Light 2: Red** (300ms) - North-south prepares to stop
6. **Light 1: Red | Light 2: Red** (300ms) - **Safety period** again
7. **Repeat**

### The setLights() Function

Instead of separate functions for each light, one function controls both:

```cpp
void setLights(TrafficLight light1, TrafficLight light2) {
  setAllOff();  // Turn everything off first
  
  // Set intersection 1
  switch (light1) {
    case RED: digitalWrite(redLight1, HIGH); break;
    // ... etc
  }
  
  // Set intersection 2
  switch (light2) {
    case RED: digitalWrite(redLight2, HIGH); break;
    // ... etc
  }
}
```

### Cleaner Main Loop

Now controlling two intersections is simple:

```cpp
void loop() {
  setLights(RED, GREEN);     // 1 stops, 2 goes
  delay(lightDelayLong);
  
  setLights(RED, YELLOW);    // 2 prepares to stop
  delay(lightDelayShort);
  
  setLights(RED, RED);       // Safety clear
  delay(lightDelayShort);
  
  setLights(GREEN, RED);     // 1 goes, 2 stops
  delay(lightDelayLong);
  
  setLights(YELLOW, RED);    // 1 prepares to stop
  delay(lightDelayShort);
  
  setLights(RED, RED);       // Safety clear
  delay(lightDelayShort);
}
```

## 💡 Key Things to Tweak

### Easy Changes

1. **Longer green for one direction** (rush hour timing):
   ```cpp
   setLights(RED, GREEN);
   delay(lightDelayLong * 2);  // Double time for one direction
   ```

2. **Flash all-red** (emergency mode):
   ```cpp
   void emergencyMode() {
     for (int i = 0; i < 10; i++) {
       setLights(RED, RED);
       delay(500);
       setLights(OFF, OFF);
       delay(500);
     }
   }
   ```

3. **Remove safety period** (not recommended in real life!):
   ```cpp
   // Just skip the RED, RED sections
   setLights(RED, GREEN);
   delay(lightDelayLong);
   setLights(RED, YELLOW);
   delay(lightDelayShort);
   setLights(GREEN, RED);  // Jump straight to opposite
   ```

### Intermediate Changes

4. **Pedestrian crossing** - Add walk signals:
   ```cpp
   const int WALK1 = 8;
   const int WALK2 = 4;
   
   void setPedestrianSignals(bool walk1, bool walk2) {
     digitalWrite(WALK1, walk1 ? HIGH : LOW);
     digitalWrite(WALK2, walk2 ? HIGH : LOW);
   }
   
   void loop() {
     setLights(RED, GREEN);
     setPedestrianSignals(true, false);  // Walk sign for intersection 1
     // ... etc
   }
   ```

5. **Sensor-triggered** - Button to request green:
   ```cpp
   const int SENSOR1 = 2;
   const int SENSOR2 = 3;
   
   void loop() {
     setLights(RED, GREEN);
     
     // Check if intersection 1 has waiting cars
     if (digitalRead(SENSOR1) == LOW) {
       delay(lightDelayLong);  // Give full time
     } else {
       delay(lightDelayShort);  // Skip early if no cars
     }
     // ... continue sequence ...
   }
   ```

6. **Time-of-day logic** - Different timing by time:
   ```cpp
   unsigned long currentTime = millis();
   int greenTime;
   
   if (currentTime < 30000) {  // First 30 seconds
     greenTime = lightDelayShort;  // Night mode (short greens)
   } else {
     greenTime = lightDelayLong * 2;  // Rush hour (long greens)
   }
   
   setLights(RED, GREEN);
   delay(greenTime);
   ```

### Advanced Challenges

7. **Three-way intersection** - Add a third direction

8. **Turn arrows** - Add dedicated left-turn signals

9. **Adaptive timing** - Count how long it's been since each direction got green, prioritize the longest wait

10. **Fully state-machine based** - Use enums for states, transitions, and timers instead of delays

## 🎓 What You're Learning

- **Multi-output coordination** - Managing 6 outputs that must work together
- **Safety logic** - Ensuring dangerous states (both green) never happen
- **Function parameters** - Passing multiple values to functions
- **Real-world systems** - How actual traffic lights work
- **Sequence design** - Planning complex timing patterns

## 🐛 Common Issues

**Both lights green at same time:**
- Bug in the sequence - review your `setLights()` calls
- Make sure you never call `setLights(GREEN, GREEN)`

**Jerky or stuttering timing:**
- Delays might be too short
- Increase `lightDelayShort` and `lightDelayLong`

**One intersection not working:**
- Check wiring for that set of LEDs
- Verify pin numbers in code match hardware

## 🎯 Safety First!

Notice how the code **never allows both greens**:
- Every state is either `(RED, GREEN)` or `(GREEN, RED)`
- Transition states use `(RED, YELLOW)` or `(YELLOW, RED)`
- Safety states use `(RED, RED)`

This is how real traffic lights prevent accidents!

## 🔗 Next Steps

- Try [traffic__two_function_led](../traffic__two_function_led/README.md) - Same logic, different hardware
- Add sensors or buttons for interactive control
- Build a 4-way intersection (needs more pins!)

---

**Coordinate the chaos! 🚦🚦**
