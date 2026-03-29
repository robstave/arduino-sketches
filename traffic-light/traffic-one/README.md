# Traffic-One - Basic Traffic Light Sequence

## 🎯 What This Project Does

This sketch controls a single traffic light, cycling through red → green → yellow → repeat. All the code is written in a simple, straightforward way that's easy to read from top to bottom.

## 🔌 Hardware Setup

Follow the main [traffic-light folder README](../README.md) for wiring 3 LEDs to pins 11, 12, and 13.

## 📊 How It Works

### The Sequence

1. **All lights off except Red** - Wait 899ms (just under 1 second)
2. **All lights off except Green** - Wait 899ms
3. **All lights off except Yellow** - Wait 300ms (quick flash)
4. **Repeat forever**

### Flat Code Structure

This sketch intentionally does NOT use functions. Everything happens in `loop()`:

```cpp
void loop() {
  digitalWrite(greenLight1, LOW);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(redLight1, HIGH);    // Red on
  delay(lightDelayLong);

  digitalWrite(greenLight1, HIGH);  // Green on
  digitalWrite(yellowLight1, LOW);
  digitalWrite(redLight1, LOW);
  delay(lightDelayLong);

  digitalWrite(greenLight1, LOW);
  digitalWrite(yellowLight1, HIGH); // Yellow on
  digitalWrite(redLight1, LOW);
  delay(lightDelayShort);
}
```

**Why flat code?** It's easier to understand for beginners - you can trace exactly what happens, line by line, without jumping to functions.

## 💡 Key Things to Tweak

### Easy Changes

1. **Change timing:**
   ```cpp
   const int lightDelayShort = 500;   // Yellow longer
   const int lightDelayLong = 2000;   // Red/Green longer
   ```

2. **Different sequence** - What if yellow comes before red?
   ```cpp
   // After green section, before red section:
   digitalWrite(greenLight1, LOW);
   digitalWrite(yellowLight1, HIGH);  // Yellow before red
   digitalWrite(redLight1, LOW);
   delay(lightDelayShort);
   ```

3. **Flash yellow** - Warning light mode:
   ```cpp
   void loop() {
     digitalWrite(yellowLight1, HIGH);
     delay(500);
     digitalWrite(yellowLight1, LOW);
     delay(500);
   }
   ```

### Intermediate Changes

4. **Add a startup sequence** - All lights on briefly at start:
   ```cpp
   void setup() {
     pinMode(redLight1, OUTPUT);
     pinMode(yellowLight1, OUTPUT);
     pinMode(greenLight1, OUTPUT);
     
     // Startup test: all on
     digitalWrite(redLight1, HIGH);
     digitalWrite(yellowLight1, HIGH);
     digitalWrite(greenLight1, HIGH);
     delay(1000);
     
     // Turn all off
     digitalWrite(redLight1, LOW);
     digitalWrite(yellowLight1, LOW);
     digitalWrite(greenLight1, LOW);
     delay(500);
   }
   ```

5. **Random timing** - Make it unpredictable:
   ```cpp
   delay(random(500, 2000));  // Instead of lightDelayLong
   ```

6. **Button-controlled** - Add a crosswalk button:
   ```cpp
   const int BUTTON_PIN = 2;
   
   void setup() {
     // ... existing setup ...
     pinMode(BUTTON_PIN, INPUT_PULLUP);
   }
   
   void loop() {
     // ... red light section ...
     
     // Check for button during green
     if (digitalRead(BUTTON_PIN) == LOW) {
       delay(2000);  // Extra green time for crossing
     }
     
     // ... rest of sequence ...
   }
   ```

## 🎓 What You're Learning

- **Digital output** - Turning LEDs on/off with `digitalWrite()`
- **Pin constants** - Using `const int` to name pins
- **Timing** - Creating delays with `delay()`
- **Sequential logic** - One step after another
- **Code reading** - Following execution top-to-bottom

## 🐛 Debugging Tips

**No lights turn on:**
- Check wiring (pins 11, 12, 13)
- Verify LEDs are oriented correctly (long leg = positive)
- Check resistors are in place

**All lights on at once:**
- Make sure you're turning lights OFF before turning new one ON
- Check for missing `digitalWrite(pin, LOW)` statements

**Wrong sequence:**
- Trace through the code line-by-line
- Add `Serial.println("Red on")` statements to track execution

**Lights flicker:**
- Normal with very short delays
- Increase delay values

## 🔗 Next Steps

Once you understand this flat structure:
1. Move to [traffic_one_function](../traffic_one_function/README.md) - See how functions clean up the code
2. Try modifying the sequence - make your own pattern!

---

**Keep it simple! 🚦**
