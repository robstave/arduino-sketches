/*
 * Car Driving LED Matrix Animation
 * For Arduino UNO R4 LED Matrix (8x12)
 * 
 * Displays a car that shifts up and down to simulate driving motion
 */

#include <Arduino.h>
#include "Arduino_LED_Matrix.h"  // Library for controlling the LED matrix

ArduinoLEDMatrix matrix;  // Create an LED matrix object  // Create an LED matrix object

// Frame buffer: A 2D array representing the LED matrix (8 rows x 12 columns)
// This is like a canvas where we draw before displaying on the actual LED matrix
// Each element is either 0 (LED off) or 1 (LED on)
uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

// Car sprite - A small pixel art image of a car (side view)
// This is a 5 rows x 10 columns array - our "drawing" of a car
// Each 1 is a lit LED, each 0 is dark
// Visual representation:
//     ####       (roof)
//   ########     (windows) 
// ##########     (body top)
// ##########     (body bottom)
//  ##    ##      (wheels)
const uint8_t car[5][10] = {
  { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },  // roof
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },  // windows
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // body top
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // body bottom  
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 }   // wheels
};

// Constants make the code easier to read and modify
// If you change the car size, just update these numbers!
const int CAR_HEIGHT = 5;  // Height of the car sprite in pixels
const int CAR_WIDTH = 10;   // Width of the car sprite in pixels

// Setup function: Runs once when the Arduino starts or resets
void setup() {
  Serial.begin(115200);  // Start serial communication for debugging (optional)
  delay(1500);           // Wait 1.5 seconds for system to stabilize
  matrix.begin();        // Initialize the LED matrix display
}

// Loop function: Runs continuously, creating the animation
void loop() {
  // This creates a simple 2-frame animation to simulate the car bouncing
  // as it drives. The car alternates between two vertical positions.
  
  // FRAME 1: Car in "up" position
  clear_frame();         // Erase everything from the previous frame
  draw_car(1, 1);        // Draw car at horizontal position 1, vertical position 1 (up)
  display_frame();       // Show the frame on the LED matrix
  delay(150);            // Hold this frame for 150 milliseconds

  // FRAME 2: Car in "down" position
  clear_frame();         // Erase the previous frame
  draw_car(1, 2);        // Draw car at horizontal position 1, vertical position 2 (down)
  display_frame();       // Show this frame on the LED matrix
  delay(150);            // Hold this frame for 150 milliseconds
  
  // The loop repeats, creating continuous motion!
}

// Clear the frame buffer by setting all LEDs to off (0)
// This is like erasing the canvas before drawing the next frame
void clear_frame() {
  for (int row = 0; row < 8; row++) {       // Loop through each row
    for (int col = 0; col < 12; col++) {    // Loop through each column
      frame[row][col] = 0;                  // Turn off this LED
    }
  }
}

// Send the current frame buffer to the LED matrix display
// This actually lights up the LEDs based on what we drew in the frame array
void display_frame() {
  matrix.renderBitmap(frame, 8, 12);  // Render the 8x12 frame on the physical matrix
}

// Draw the car sprite at a specified position on the frame
// This copies each pixel from the car array into the frame array
// Parameters:
//   offsetX - horizontal position (0-2 keeps car fully visible on 12-wide screen)
//   offsetY - vertical position (0-3 keeps car fully visible on 8-tall screen)
void draw_car(int offsetX, int offsetY) {
  // Loop through each pixel in the car sprite
  for (int row = 0; row < CAR_HEIGHT; row++) {
    for (int col = 0; col < CAR_WIDTH; col++) {
      // Calculate where this car pixel should go in the frame
      int targetRow = row + offsetY;  // Add offset to move car vertically
      int targetCol = col + offsetX;  // Add offset to move car horizontally
      
      // Boundary check: Make sure we don't try to draw outside the matrix
      // The frame is 8 rows (0-7) by 12 columns (0-11)
      if (targetRow >= 0 && targetRow < 8 && targetCol >= 0 && targetCol < 12) {
        frame[targetRow][targetCol] = car[row][col];  // Copy the pixel value
      }
    }
  }
}
