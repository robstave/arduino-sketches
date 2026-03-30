# Flyingfish-Debug - Serial Monitor Debugging Practice

## What This Project Does

This sketch is **all about learning to debug with the Serial Monitor**. It does the exact same thing as flyingfish1, but the emphasis here is on watching the sensor values in real-time to understand how the sensor behaves.

## Why This Sketch Exists

**The #1 Arduino debugging skill:** Using the Serial Monitor to watch what your sensors are doing!

Most Arduino problems come from:
- "Why isn't my sensor working?" (Answer: Check the Serial Monitor - is it reading values?)
- "Why is my LED not turning on?" (Answer: Check the Serial Monitor - what value is the sensor sending?)
- "Why does my project act weird?" (Answer: Check the Serial Monitor - are the values what you expect?)

This sketch is **practice for the most important debugging tool in your toolkit**.

## Hardware Setup

Same as flyingfish1 - see the main [ldr folder README](../README.md) for wiring.

## Using the Serial Monitor

### Opening the Serial Monitor

1. Upload the sketch to your Arduino
2. Click **Tools → Serial Monitor** (or press Ctrl+Shift+M)
3. Make sure the baud rate is set to **9600** (bottom-right of Serial Monitor window)

### What You'll See

```
 


LDR Value: 992 -> PWM: 8 | Digital (A4): 0
LDR Value: 920 -> PWM: 26 | Digital (A4): 0
LDR Value: 861 -> PWM: 41 | Digital (A4): 0
LDR Value: 500 -> PWM: 131 | Digital (A4): 1
LDR Value: 295 -> PWM: 182 | Digital (A4): 1
LDR Value: 334 -> PWM: 172 | Digital (A4): 1
```

Each line shows:
- **LDR Value** - Current analog reading (0-1023)
- **PWM** - What brightness value is being sent to the LED (0-255)
- **Digital** - Threshold state (0=below threshold, 1=above threshold)

## Debugging Experiments to Try

### Experiment 1: Understanding the Range

1. Cover the sensor with your hand
2. Watch the **LDR Value** in Serial Monitor
3. **What's the darkest value you see?** (Mine: ~50)
4. Remove your hand and shine a flashlight on it
5. **What's the brightest value you see?** (Mine: ~980)

**Why this matters:** Now you know your sensor's ACTUAL range in your environment. You can use these values to set better thresholds!

### Experiment 2: Finding the Threshold

1. Slowly adjust the potentiometer on the Flying Fish module (tiny screw)
2. Watch the **Digital** value flip between 0 and 1
3. Note what **LDR Value** causes it to change

**Example:** If Digital changes at LDR Value = 500, you know the threshold is set to detect "medium light."

### Experiment 3: Room Light Levels

Leave the sketch running and check values at different times:
- **Morning:** What value?
- **Afternoon:** What value?
- **Evening:** What value?
- **Night (lights off):** What value?

**Why this matters:** If you're making an automatic night light, you need to know what "dark" actually means in numbers!

### Experiment 4: PWM Mapping

1. Watch how **LDR Value** changes with light
2. Watch how **PWM** changes in the opposite direction
3. Verify that when LDR is high (bright), PWM is low (dim LED)

**Challenge:** Modify the code to reverse this relationship!

## Debugging Tips for Your Own Projects

**Problem:** "My sensor isn't working"
- **Debug step:** Open Serial Monitor. Is it printing anything? If yes, sensor IS working - your code might be the issue!

**Problem:** "My threshold isn't triggering"
- **Debug step:** Watch the analog values. Are they ever crossing your threshold number? If not, adjust the threshold!

**Problem:** "Values are jumping around"
- **Debug step:** If you see values like 450, 455, 448, 452 - that's normal sensor noise. Add smoothing (averaging).

**Problem:** "Sensor reads the same value always"
- **Debug step:** Always 0 or 1023 = bad connection. Always the same mid-value = something in code is overwriting it.

## What You're Learning

- **Serial debugging** - The most critical Arduino skill
- **Sensor calibration** - Understanding what "dark" and "bright" mean in numbers
- **Threshold tuning** - Setting cut-off points based on real data
- **Troubleshooting methodology** - Check the data first, then the code

## 🔧 Challenge: Add More Debug Info

Try adding these debug lines to learn more:

```cpp
Serial.print("Time: ");
Serial.print(millis());
Serial.print(" ms | ");
// ...existing print statements...

// Or print in CSV format for graphing:
Serial.print(ldrValue);
Serial.print(",");
Serial.println(pwmValue);
```

Then you can:
- See how values change over time
- Copy data into Excel/Sheets to make graphs
- Create a "light level over 24 hours" chart

## 🔗 Next Steps

Master the Serial Monitor here, then move to:
- [flyingfishled](../flyingfishled/README.md) - Visualize the data on the LED matrix
- Your own projects - use Serial Monitor debugging in EVERYTHING you build!

---

**Debug like a pro! 🔍**
