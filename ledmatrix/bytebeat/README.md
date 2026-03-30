# Bytebeat Audio Visualizer

## What This Project Does

This sketch generates music or sound patterns using mathematical formulas (called "bytebeat"), then visualizes the audio waveform on the LED matrix in real-time.

## What is Bytebeat?

Bytebeat is a technique for creating music using simple mathematical expressions. By combining counters, bit operations, and modulo arithmetic, you can generate surprisingly complex musical patterns from just one line of code!

**Example bytebeat formula:**
```cpp
output = (t * 5 & t >> 7) | (t * 3 & t >> 10);
```

Where `t` is a counter that increments each sample, creating evolving patterns over time.

## Status

This project is currently **under development**. Check back soon for:
- Multiple bytebeat formulas to choose from
- Real-time waveform visualization on the LED matrix
- Interactive controls to modify the formulas
- Audio output options

## Learn More

- [Bytebeat on Wikipedia](https://en.wikipedia.org/wiki/Bytebeat)
- [Bytebeat Playground](http://greggman.com/downloads/examples/html5bytebeat/html5bytebeat.html)
- [Arduino Audio Output Guide](https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody)

---

**Coming soon!**
