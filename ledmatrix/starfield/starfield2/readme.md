# Starfield Animation for Arduino UNO R4 with Joystick

This sketch creates a "warp speed" starfield effect on the Arduino UNO R4 WiFi's 12x8 LED matrix. Stars appear in the center and radiate outwards, simulating forward movement through space.

You can steer the "ship" using an analog joystick connected to pins A0 and A1.

## Hardware Setup

- **Joystick X-Axis:** Pin A0
- **Joystick Y-Axis:** Pin A1
- **Joystick VCC:** 5V
- **Joystick GND:** GND

## How it works

The code builds upon the simple starfield animation by adding camera movement through space.

### 1. The 3D World
We store a list of stars, each with 3 coordinates:
*   **X**: Horizontal position in space (left/right)
*   **Y**: Vertical position in space (up/down)
*   **Z**: Depth (distance from the camera)

### 2. Forward Movement
To simulate moving *forward* through space, we decrease the **Z** coordinate of every star in each frame.
$$ Z_{new} = Z_{old} - speed $$

### 3. Turning (Camera Rotation/Strafing)
To simulate turning the spaceship, we shift the entire universe in the opposite direction.
When you push the joystick **Right**, the camera should turn right. In the star's frame of reference, this means the stars should move **Left**.

We modify the X and Y coordinates of every star based on the joystick input:
$$ X_{star} = X_{star} - Joystick_{turnX} $$
$$ Y_{star} = Y_{star} - Joystick_{turnY} $$

This creates the illusion that the ship is changing direction.

### 4. Perspective Projection (The "Divide by Z")
To draw a 3D star on a 2D screen, we separate the coordinates into their perspective components. The core trick of 3D graphics is **perspective division**: objects that are further away (larger Z) appear smaller and closer to the center of vision.

The formula used describes this relationship:
$$ x_{screen} = \frac{X_{world}}{Z} + CenterX $$
$$ y_{screen} = \frac{Y_{world}}{Z} + CenterY $$

*   If $Z$ is large (far away), the fraction is small $\to$ the star is drawn near the center.
*   If $Z$ is small (close), the fraction is large $\to$ the star moves rapidly towards the edge.

This simple division creates the illusion of depth and speed.

## Uploading

1. Open `starfield2.ino` in Arduino IDE.
2. Select **Arduino UNO R4 WiFi** as the board.
3. Upload.
