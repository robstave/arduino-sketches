# Starfield Animation for Arduino UNO R4

This sketch creates a "warp speed" starfield effect on the Arduino UNO R4 WiFi's 12x8 LED matrix. Stars appear in the center and radiate outwards, simulating forward movement through space.

## How it works

The animation uses a classic 3D-to-2D projection algorithm. 

### 1. The 3D World
We store a list of stars, each with 3 coordinates:
*   **X**: Horizontal position in space (left/right)
*   **Y**: Vertical position in space (up/down)
*   **Z**: Depth (distance from the camera)

### 2. Movement
To simulate moving *forward* through space, we decrease the **Z** coordinate of every star in each frame.
$$ Z_{new} = Z_{old} - speed $$
When a star passes behind the camera ($Z \le 0$), we "respawn" it at the far back with new random X and Y coordinates.

### 3. Perspective Projection (The "Divide by Z")
To draw a 3D star on a 2D screen, we need to convert $(X, Y, Z)$ into $(Row, Col)$.
The core trick of 3D graphics is **perspective division**: objects that are further away (larger Z) appear smaller and closer to the center of vision.

The formula used describes this relationship:
$$ x_{screen} = \frac{X_{world}}{Z} + CenterX $$
$$ y_{screen} = \frac{Y_{world}}{Z} + CenterY $$

*   If $Z$ is large (far away), the fraction is small $\to$ the star is drawn near the center.
*   If $Z$ is small (close), the fraction is large $\to$ the star moves rapidly towards the edge.

This simple division creates the illusion of depth and speed.

## Uploading

1. Open `starfield1.ino` in Arduino IDE.
2. Select **Arduino UNO R4 WiFi** (or Minima) as the board.
3. Upload.
