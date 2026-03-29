/*
 * Eye1 - Interactive Eyeball Animation
 * For Arduino UNO R4 LED Matrix (8x12)
 * 
 * DESCRIPTION:
 * This sketch creates a realistic eyeball that responds to a joystick.
 * Move the joystick to look around, press the button to blink.
 * 
 * HARDWARE REQUIRED:
 * - Arduino UNO R4 WiFi
 * - Analog Joystick Module
 * 
 * WIRING:
 * - Joystick VCC → 5V
 * - Joystick GND → GND  
 * - Joystick VRx → A0 (X-axis)
 * - Joystick VRy → A1 (Y-axis)
 * - Joystick SW  → A2 (Button)
 * 
 * JOYSTICK TUTORIAL:
 * https://arduinogetstarted.com/tutorials/arduino-joystick
 */
#include <Arduino.h>
#include "Arduino_LED_Matrix.h"  // Library for controlling the LED matrix

ArduinoLEDMatrix matrix;  // Create an LED matrix object

// Joystick Pin Configuration
// An analog joystick has two potentiometers (X and Y) and a button
const int PIN_X = A0;      // Joystick X-axis (horizontal: left/right)
const int PIN_Y = A1;      // Joystick Y-axis (vertical: up/down)
const int PIN_BTN = A2;    // Joystick button (pressed to blink)

// Frame buffer: 2D array representing the LED matrix (8 rows x 12 columns)
// Each element is either 0 (LED off/dark) or 1 (LED on/bright)
uint8_t frame[8][12];

// EYE DESIGN:
// The eye consists of:
//   1. Sclera (white part) - An oval shape filling most of the screen
//   2. Pupil (dark center) - A 2x2 pixel black square that moves around
// 
// The pupil position is controlled by the joystick:
//   X range: 2 to 8 (keeps 2x2 pupil within the 12-column screen)
//   Y range: 1 to 5 (keeps 2x2 pupil within the 8-row screen)

// Function Prototypes
void drawEye(int px, int py, float openness);  // Draw eye with pupil at (px,py), openness 0.0-1.0
void blinkEye(int px, int py);                 // Animate a blink at current pupil position
void clearFrame();                              // Clear all LEDs in the frame buffer

// Setup function: Runs once when the Arduino starts or resets
void setup() {
  Serial.begin(115200);  // Start serial communication for debugging (optional)
  matrix.begin();        // Initialize the LED matrix display
  
  // Configure joystick pins
  pinMode(PIN_X, INPUT);           // X-axis is an analog input (0-1023)
  pinMode(PIN_Y, INPUT);           // Y-axis is an analog input (0-1023)
  pinMode(PIN_BTN, INPUT_PULLUP);  // Button uses internal pull-up resistor
                                   // (LOW when pressed, HIGH when released)
}

// Loop function: Runs continuously to update the eye animation
void loop() {
  // STEP 1: Read joystick position
  // analogRead() returns a value from 0 to 1023:
  //   - 0 = Joystick pushed fully to one side
  //   - 512 = Centered (neutral position)
  //   - 1023 = Joystick pushed fully to the other side
  int joyX = analogRead(PIN_X);  // Read horizontal position
  int joyY = analogRead(PIN_Y);  // Read vertical position
  
  // STEP 2: Convert joystick values to pupil screen coordinates
  // map(value, fromLow, fromHigh, toLow, toHigh) scales the input range to output range
  // 
  // Why these ranges?
  // - Pupil is 2x2 pixels (occupies positions px to px+1, py to py+1)
  // - Screen is 12 columns wide: pupil X can go from 2 to 8 (leaving room for eye shape)
  // - Screen is 8 rows tall: pupil Y can go from 1 to 5 (leaving room at top/bottom)
  // 
  // NOTE: If the eye moves in the wrong direction, swap the last two numbers
  //       For example: map(joyX, 0, 1023, 8, 2) would reverse left/right
  int pupilX = map(joyX, 0, 1023, 2, 8);  // Horizontal: joystick 0-1023 → screen 2-8
  int pupilY = map(joyY, 0, 1023, 1, 5);  // Vertical: joystick 0-1023 → screen 1-5
  
  // STEP 3: Safety check - ensure values stay within bounds
  // constrain(value, min, max) forces a value to stay within a range
  pupilX = constrain(pupilX, 2, 8);  // Keep pupilX between 2 and 8
  pupilY = constrain(pupilY, 1, 5);  // Keep pupilY between 1 and 5

  // STEP 4: Check if button is pressed to trigger a blink
  // INPUT_PULLUP means: HIGH = not pressed, LOW = pressed
  if (digitalRead(PIN_BTN) == LOW) {
    // Button is pressed - trigger blink animation
    blinkEye(pupilX, pupilY);  // Animate closing and opening the eye
    
    // DEBOUNCE: Wait for user to release button before continuing
    // This prevents multiple blinks from a single button press
    delay(200);  // Small delay to avoid bouncing
    while(digitalRead(PIN_BTN) == LOW);  // Wait until button is released
  } else {
    // STEP 5: Normal operation - draw open eye with pupil at joystick position
    drawEye(pupilX, pupilY, 1.0);  // 1.0 = fully open eye
  }
  
  // STEP 6: Control frame rate
  delay(30);  // Wait 30ms between updates (~33 frames per second)
}               // This gives smooth animation while not overloading the processor

// Draw the eye with specified pupil position and openness
// Parameters:
//   px - Pupil X position (horizontal, 2-8)
//   py - Pupil Y position (vertical, 1-5)
//   openness - How open the eye is (0.0 = closed, 1.0 = fully open)
void drawEye(int px, int py, float openness) {
  clearFrame();  // Start with a blank frame
  
  // PART 1: Draw the Sclera (the white part of the eye)
  // We create an oval shape by turning on LEDs in an elliptical pattern
  // Strategy: Turn on all LEDs, then turn off corners and edges to make it round
  
  // Loop through every pixel on the display
  for (int y = 0; y < 8; y++) {           // For each row (0-7)
    for (int x = 0; x < 12; x++) {        // For each column (0-11)
      // Start by assuming this pixel is part of the white of the eye
      bool isSclera = true;
      
      // SHAPING: Cut off corners to make the eye oval instead of rectangular
      // Top and bottom rows: trim the left and right edges
      if ((y == 0 || y == 7) && (x < 2 || x > 9)) 
        isSclera = false;  // Corner pixels are dark
      
      // Second and second-to-last rows: trim even more
      if ((y == 1 || y == 6) && (x < 1 || x > 10)) 
        isSclera = false;
      
      // EYELID ANIMATION: Control how much of the eye is visible
      // The vertical center of the screen is at y = 3.5 (between rows 3 and 4)
      // When the eye closes, only rows near the center remain visible
      // 
      // Calculate maximum allowed distance from center based on openness:
      //   openness = 1.0 → maxDist = 4.0 (all 8 rows visible)
      //   openness = 0.5 → maxDist = 2.0 (only middle 4 rows visible)
      //   openness = 0.0 → maxDist = 0.0 (eye completely closed)
      float maxDist = 4.0 * openness;
      if (abs(y - 3.5) > maxDist)  // If this row is too far from center
        isSclera = false;           // It's hidden by the eyelid

      // Turn on the LED if this pixel is part of the visible sclera
      if (isSclera) {
        frame[y][x] = 1;  // 1 = LED on (white)
      }
    }
  }
  
  // PART 2: Draw the Pupil (the dark center that moves around)
  // Only draw the pupil if the eye is open enough to see it
  if (openness > 0.2) {  // Don't show pupil when eye is nearly closed
    
    // The pupil is a 2x2 square of dark pixels at position (px, py)
    // It occupies 4 pixels:
    //   (px, py)     (px+1, py)      ← Top row of pupil
    //   (px, py+1)   (px+1, py+1)    ← Bottom row of pupil
    
    // Boundary check: make sure all 4 pixels fit on the screen
    if(px >= 0 && px < 11 && py >= 0 && py < 7) {
       frame[py][px] = 0;        // Top-left pixel: dark
       frame[py][px+1] = 0;      // Top-right pixel: dark
       frame[py+1][px] = 0;      // Bottom-left pixel: dark
       frame[py+1][px+1] = 0;    // Bottom-right pixel: dark
       
       // OPTIONAL ENHANCEMENT: You could add a white "shine" pixel here
       // to make the eye look more realistic (like a light reflection)
       // Example: frame[py][px+1] = 1; (turn top-right pixel white)
    }
  }
  
  // Send the completed frame to the LED matrix display
  matrix.renderBitmap(frame, 8, 12);
}

// Animate a blink at the current pupil position
// This creates a smooth closing and opening animation
// Parameters:
//   px, py - Current pupil position (stays the same during blink)
void blinkEye(int px, int py) {
  
  // PHASE 1: Closing animation (eye gradually closes)
  // Start at fully open (1.0) and decrease to fully closed (0.0)
  // Each step reduces openness by 0.15, creating about 7 frames
  for (float open = 1.0; open >= 0.0; open -= 0.15) {
     drawEye(px, py, open);  // Redraw eye with new openness value
     delay(40);              // Wait 40ms between frames (smooth animation)
  }
  
  // PHASE 2: Eye stays closed briefly
  drawEye(px, py, 0.0);  // Draw completely closed eye
  delay(150);            // Hold for 150ms (realistic blink pause)
  
  // PHASE 3: Opening animation (eye gradually opens)
  // Start at fully closed (0.0) and increase to fully open (1.0)
  for (float open = 0.0; open <= 1.0; open += 0.15) {
     drawEye(px, py, open);  // Redraw eye with increasing openness
     delay(40);              // Wait 40ms between frames
  }
  
  // Total blink time: ~7 frames × 40ms × 2 + 150ms ≈ 700ms (about 0.7 seconds)
}

// Clear the frame buffer by turning off all LEDs
// This is like erasing the canvas before drawing the next frame
void clearFrame() {
  for (int i = 0; i < 8; i++)       // Loop through each row
    for (int j = 0; j < 12; j++)    // Loop through each column
      frame[i][j] = 0;              // Set LED to off (dark)
}
