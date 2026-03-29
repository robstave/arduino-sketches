# Flyingfish1 - Basic LDR Sensor Reading

## 🎯 What This Project Does

This sketch reads light levels from the Flying Fish LDR sensor module and controls an LED's brightness based on the light level. It's the foundation for understanding how light sensors work with Arduino.

## 🔌 Hardware Setup

Follow the main [ldr folder README](../README.md) for wiring the Flying Fish module to pins A5 (analog), A4 (digital), and pin 13 (output).

## 📊 How It Works

### Reading the Sensor

The sketch reads two values from the LDR module every 100ms:

1. **Analog value** (0-1023) - Continuous light level measurement
   - 0 = Very dark
   - 512 = Medium light
   - 1023 = Very bright

2. **Digital value** (HIGH/LOW) - Threshold comparison
   - LOW = Light level below threshold (dark)
   - HIGH = Light level above threshold (bright)
   - Threshold set by potentiometer on the module

### Controlling the LED

The analog light level is mapped to LED brightness:
```cpp
int pwmValue = map(ldrValue, 0, 1023, 255, 0);
```

**Note the reversal:** When light is HIGH (1023), LED brightness is LOW (0), and vice versa. This creates a "night light" effect - the LED gets brighter as it gets darker!

### Serial Output

The sketch prints sensor values to the Serial Monitor:
```
LDR Value: 450 -> PWM: 134 | Digital (A4): 0
```

## 💡 Key Things to Tweak

### Easy Changes

1. **Reverse the LED behavior** (make it bright when light is bright):
   ```cpp
   int pwmValue = map(ldrValue, 0, 1023, 0, 255);  // Swap 0 and 255
   ```

2. **Change update speed**:
   ```cpp
   delay(100);  // Try 50 (faster) or 500 (slower)
   ```

3. **Adjust output range** (dim LED even at brightest):
   ```cpp
   int pwmValue = map(ldrValue, 0, 1023, 128, 0);  // Max brightness = 128
   ```

### Intermediate Changes

4. **Add a threshold** (only turn on LED when very dark):
   ```cpp
   if (ldrValue < 300) {
     analogWrite(OUTPUT_PIN, pwmValue);
   } else {
     analogWrite(OUTPUT_PIN, 0);  // Off when bright
   }
   ```

5. **Smooth the readings** (average last few values to reduce flickering):
   ```cpp
   // Add before loop():
   const int NUM_READINGS = 5;
   int readings[NUM_READINGS];
   int readIndex = 0;
   
   // In loop():
   readings[readIndex] = analogRead(LDR_ANALOG_PIN);
   readIndex = (readIndex + 1) % NUM_READINGS;
   int average = 0;
   for(int i = 0; i < NUM_READINGS; i++) average += readings[i];
   int ldrValue = average / NUM_READINGS;
   ```

## 🐛 Debugging Tips

**Open the Serial Monitor** (Tools → Serial Monitor or Ctrl+Shift+M) and watch the values:

- **LDR Value always 0 or 1023:** Check wiring, module might be disconnected
- **LED not changing:** Verify pin 13 is connected, check PWM mapping direction
- **Digital value stuck:** Adjust the onboard potentiometer screw on the module
- **Erratic readings:** Sensor might be in transitional lighting or need smoothing

## 🎓 What You're Learning

- **Analog input:** Reading continuous sensor values with `analogRead()`
- **Digital input:** Reading binary states with `digitalRead()`
- **Value mapping:** Converting one range to another with `map()`
- **PWM output:** Controlling LED brightness with `analogWrite()`
- **Serial debugging:** Using `Serial.print()` to see what's happening

## 🔗 Next Steps

Once this works reliably:
1. Move to [flyingfish-debug](../flyingfish-debug/README.md) to practice Serial Monitor debugging
2. Try [flyingfishled](../flyingfishled/README.md) to visualize data on the LED matrix

---

**Sense the light! 💡**
