# Traffic_One_Function - Functions and Enums

## 🎯 What This Project Does

This sketch creates the same traffic light sequence as traffic-one, but introduces **functions** and **enums** to make the code more organized and readable.

## 🔌 Hardware Setup

Identical to traffic-one - see the main [traffic-light folder README](../README.md) for wiring.

## 📊 How It Works

### Introducing Enums

Instead of writing "red", "green", "yellow" everywhere, we define an enum:

```cpp
enum TrafficLight {
  OFF,
  RED,
  YELLOW,
  GREEN
};
```

Now we can write `setLight1(RED)` instead of juggling three separate `digitalWrite()` calls!

### The setLight1() Function

This function takes an enum value and sets the lights accordingly:

```cpp
void setLight1(TrafficLight light) {
  switch (light) {
    case RED:
      digitalWrite(redLight1, HIGH);
      break;
    case YELLOW:
      digitalWrite(yellowLight1, HIGH);
      break;
    case GREEN:
      digitalWrite(greenLight1, HIGH);
      break;
    case OFF:
      // All lights already off
      break;
  }
}
```

### Cleaner loop()

Now the main loop is much more readable:

```cpp
void loop() {
  setLight1(RED);
  delay(lightDelayLong);

  setLight1(GREEN);
  delay(lightDelayLong);

  setLight1(YELLOW);
  delay(lightDelayShort);
}
```

## 🐛 The Bug!

**This sketch has a bug!** Look at the `setLight1()` function:

```cpp
void setLight1(TrafficLight light) {
  switch (light) {
    digitalWrite(redLight1, LOW);    // <-- BUG! Outside any case
    digitalWrite(yellowLight1, LOW);
    digitalWrite(greenLight1, LOW);

  case RED:
    digitalWrite(redLight1, HIGH);
    break;
  // ... etc
}
```

The `digitalWrite(LOW)` calls are OUTSIDE the switch cases, so they execute BEFORE the switch even runs. This means they happen every time, regardless of which light you're trying to turn on.

**Why it still works:** The LOW calls happen first, turning everything off. Then the switch turns one light back on. The result is correct, but inefficient.

**How to fix it:**
```cpp
void setLight1(TrafficLight light) {
  // Turn all off first
  digitalWrite(redLight1, LOW);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(greenLight1, LOW);
  
  // Then turn on the requested light
  switch (light) {
    case RED:
      digitalWrite(redLight1, HIGH);
      break;
    // ... etc
  }
}
```

This is great practice for debugging - the code works but isn't quite right!

## 💡 Key Things to Tweak

### Easy Changes

1. **Add more states** - Create a flashing yellow mode:
   ```cpp
   enum TrafficLight {
     OFF,
     RED,
     YELLOW,
     GREEN,
     FLASH_YELLOW  // New state
   };
   
   void loop() {
     setLight1(FLASH_YELLOW);
     // ... blink yellow in here ...
   }
   ```

2. **Different sequences** - Try all-lights-on for testing:
   ```cpp
   setLight1(RED);
   digitalWrite(yellowLight1, HIGH);  // Multiple lights at once
   digitalWrite(greenLight1, HIGH);
   delay(1000);
   ```

### Intermediate Changes

3. **Fix the bug** (see above)

4. **Add return values** - Function confirms success:
   ```cpp
   bool setLight1(TrafficLight light) {
     // ... turn off lights ...
     
     switch (light) {
       case RED:
       case YELLOW:
       case GREEN:
         // ... turn on light ...
         return true;
       default:
         return false;  // Invalid state
     }
   }
   ```

5. **Transition function** - Fade between colors smoothly:
   ```cpp
   void transition(TrafficLight from, TrafficLight to, int steps) {
     for (int i = 0; i < steps; i++) {
       setLight1(from);
       delay(50);
       setLight1(OFF);
       delay(50);
     }
     setLight1(to);
   }
   ```

## 🎓 What You're Learning

- **Functions** - Reusable blocks of code
- **Enums** - Named constants instead of magic numbers
- **Switch statements** - Multi-way branching
- **Code organization** - Separating "what" from "how"
- **Debugging** - Finding and fixing logical errors

## 🔗 Why Functions Matter

Compare this:
```cpp
// Without function
digitalWrite(greenLight1, LOW);
digitalWrite(yellowLight1, LOW);
digitalWrite(redLight1, LOW);
digitalWrite(redLight1, HIGH);
```

To this:
```cpp
// With function
setLight1(RED);
```

**Benefits:**
- Easier to read
- Less typing
- Fewer mistakes
- Easier to modify (change function once, affects all calls)

## 🔗 Next Steps

Once you're comfortable with functions and enums:
1. Move to [traffic__two_function](../traffic__two_function/README.md) - Control two intersections!
2. Try creating your own functions for different patterns

---

**Function for the win! 🚦✨**
