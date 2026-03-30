# Car Driving LED Matrix Animation

## What This Project Does

This Arduino sketch creates a simple animation of a car "driving" on the Arduino UNO R4's built-in LED matrix display. The car bounces up and down slightly to simulate the motion of driving over a bumpy road.

## Hardware Required

- **Arduino UNO R4 WiFi** (the board with the built-in 8x12 LED matrix)
 

## What You'll Learn

- Creating sprite graphics (small pixel art images)
- Animation basics using frame-by-frame changes
- Working with 2D arrays for graphics
- Using constants to make code more readable
- Drawing objects at different positions on a screen
- Boundary checking (keeping sprites within screen limits)

## How It Works

### The Car Sprite

The car is defined as a 5x10 pixel image stored in the `car` array:
```
    ####        (roof)
  ########      (windows)
##########      (body top)
##########      (body bottom)
 ##    ##       (wheels)
```

Each `1` represents a lit LED, and each `0` is an LED that's off.

### The Animation

The animation is simple but effective:
1. Draw the car at vertical position 1 (slightly up)
2. Wait 150 milliseconds
3. Draw the car at vertical position 2 (slightly down)
4. Wait 150 milliseconds
5. Repeat forever!

This creates the illusion of the car bouncing as it drives, making it look more dynamic than a static image.

### How Drawing Works

The `draw_car()` function copies each pixel from the car sprite into the frame buffer at a specified position:
- `offsetX` controls horizontal position (left/right)
- `offsetY` controls vertical position (up/down)
- Boundary checking ensures we don't try to draw outside the 8x12 matrix

## Try These Modifications

### Beginner Level
1. **Change the speed**: Modify the `delay(150)` values to make the car bounce faster or slower
2. **Change position**: Try different offsetX values to move the car left or right
3. **Add more frames**: Create a third position to make the bounce smoother

### Intermediate Level
1. **Horizontal movement**: Make the car scroll across the screen from left to right
2. **Design a new vehicle**: Create a different sprite (truck, motorcycle, spaceship, etc.)
3. **Add a road**: Draw a line at the bottom to represent the ground
4. **Add scenery**: Create trees, buildings, or clouds that scroll past

### Advanced Level
1. **Parallax scrolling**: Make background objects move slower than foreground objects
2. **Multiple vehicles**: Display several cars at different positions
3. **Road obstacles**: Add objects the car needs to "avoid" (just visual, or make it interactive)
4. **Speed control**: Use the Serial Monitor to control animation speed
5. **Create a game**: Add user input to move the car up/down to dodge obstacles

## Creating Your Own Sprites

To create your own sprite:

1. Draw your design on graph paper (remember: 8 rows max, 12 columns max)
2. Convert each row to 1s and 0s (1 = lit LED, 0 = dark LED)
3. Create a 2D array like the car sprite
4. Update the `CAR_HEIGHT` and `CAR_WIDTH` constants

Example - A simple smiley face (5x5):
```cpp
const uint8_t smiley[5][5] = {
  { 0, 1, 0, 1, 0 },  // eyes
  { 0, 0, 0, 0, 0 },  // 
  { 1, 0, 0, 0, 1 },  // smile
  { 0, 1, 1, 1, 0 },  // 
  { 0, 0, 0, 0, 0 }   // 
};
```

## Animation Concepts

### Frame Rate
The delay between frames (150ms) gives us about 6-7 frames per second. This is the "frame rate" - how fast the animation updates.

- **Faster** (smaller delay): Smoother motion but might be too quick
- **Slower** (larger delay): More visible but can look choppy

### Persistence of Vision
Your eyes hold onto images for a split second after seeing them. When images change fast enough (usually 15+ frames per second), your brain blends them together, creating the illusion of smooth motion. That's how movies, TV, and this car animation work!

## Resources

- [Arduino UNO R4 WiFi Documentation](https://docs.arduino.cc/hardware/uno-r4-wifi)
- [Arduino LED Matrix Library Reference](https://docs.arduino.cc/tutorials/uno-r4-wifi/led-matrix)
- [Pixel Art Basics](https://en.wikipedia.org/wiki/Pixel_art)

## 📄 License

This code is in the public domain. Feel free to use and modify it for your own projects!

---

 
