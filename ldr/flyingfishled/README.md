# Flyingfishled - LED Matrix Light Visualization

## What This Project Does

This sketch combines the light sensor from flyingfish1 with the Arduino UNO R4's built-in LED matrix to create a live visual display of light levels. It's perfect for seeing sensor data at a glance without needing the Serial Monitor!

## Hardware Required

- **Arduino UNO R4 WiFi** (for the built-in LED matrix)
- **Flying Fish LDR Module** wired as usual (see [main ldr README](../README.md))

## The Display

The LED matrix is divided into two sections:

### Top Half (Rows 0-3): Analog Bar Chart

Shows the light level as a horizontal bar:
- **No light** = Empty (all dark)
- **Medium light** = Half-width bar (6 columns lit)
- **Bright light** = Full-width bar (all 12 columns lit)

The width represents the analog value (0-1023) mapped to screen width (0-12 columns).

### Bottom Half (Rows 4-7): Digital Threshold Indicator

Shows the digital threshold state:
- **Below threshold** (dark) = Empty (all dark)
- **Above threshold** (bright) = Filled (all 48 LEDs lit)

This creates a clear visual: when the bottom half lights up, you know the sensor has crossed the threshold!

## How It Works

### Bar Chart Mapping

```cpp
int barWidth = map(analogVal, 0, 1023, 0, 12);
```

The analog sensor value (0-1023) is converted to a column count (0-12). Then rows 0-3 are filled up to that column.

### Digital Indicator

```cpp
if (digitalVal == 1) {
  // Fill rows 4-7 completely
}
```

When the digital pin reads HIGH (light above threshold), the entire bottom half lights up as a solid block.

## Key Things to Tweak

### Easy Changes

1. **Reverse the bar** (darker = longer bar):
   ```cpp
   int barWidth = map(analogVal, 0, 1023, 12, 0);  // Swap 0 and 12
   ```

2. **Change update speed**:
   ```cpp
   delay(100);  // Try 50 (faster updates) or 200 (slower)
   ```

3. **Invert the digital indicator** (show when it's DARK):
   ```cpp
   if (digitalVal == 0) {  // Change 1 to 0
     // Fill bottom half
   }
   ```

### Intermediate Changes

4. **Add a center line** (mark the middle of the display):
   ```cpp
   // After drawing the bar, before rendering:
   for (int r = 0; r < 4; r++) {
     frame[r][6] = !frame[r][6];  // Toggle middle column
   }
   ```

5. **Vertical bars instead of horizontal**:
   ```cpp
   int barHeight = map(analogVal, 0, 1023, 0, 8);
   for (int r = 8 - barHeight; r < 8; r++) {
     for (int c = 0; c < 12; c++) {
       frame[r][c] = 1;
     }
   }
   ```

6. **Show both values as separate bars**:
   ```cpp
   // Top 4 rows: Analog (0-12 wide)
   // Bottom 4 rows: PWM output (0-12 wide mapped from 0-255)
   ```

### Advanced Challenges

7. **Scrolling history graph:** Keep last 12 readings and scroll them left, showing light level over time

8. **Threshold line:** Draw a vertical line at the position where the digital threshold is set

9. **Sparkle effect:** Make individual LEDs flicker based on light intensity

10. **Waveform:** Show a sine wave that speeds up/slows down based on light level

## 🎓 What You're Learning

- **Data visualization** - Turning numbers into visual representations
- **Frame buffer manipulation** - Directly setting LED matrix pixels
- **Multi-region displays** - Using different screen areas for different data
- **Real-time updates** - Refreshing a display continuously

## 🐛 Debugging Tips

**Bar not showing:**
- Check that `barWidth` is being calculated (add Serial.print to verify)
- Verify the loop ranges are correct (rows 0-3, columns 0-barWidth)

**Bottom half stuck on/off:**
- Print `digitalVal` to Serial Monitor - is it changing?
- Adjust the potentiometer on the Flying Fish module

**Display flickering:**
- Normal! The matrix updates every frame. To reduce flicker, increase the delay time.

**Wrong values showing:**
- Verify the mapping: print both `analogVal` and `barWidth` to Serial Monitor
- Check that you're using the correct pins (A5 for analog, A4 for digital)

## 🔗 Related Projects

- [flyingfish1](../flyingfish1/README.md) - Basic sensor reading
- [flyingfish-debug](../flyingfish-debug/README.md) - Serial Monitor debugging practice
- [alphanum](../../ledmatrix/alphanum/README.md) - More LED matrix display examples

---

**Visualize the light! 📊✨**
