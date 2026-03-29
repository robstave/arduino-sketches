/*
 * Alphanumeric LED Matrix Display
 * 
 * Created by ArduinoGetStarted.com
 * This example code is in the public domain
 * 
 * Font source and tutorial: 
 * https://arduinogetstarted.com/tutorials/arduino-uno-r4-led-matrix-displays-number-character
 * 
 * DESCRIPTION:
 * This program displays numbers (0-9) and letters (A-Z) on the Arduino UNO R4's
 * built-in LED matrix. Each character is shown for 1 second.
 */

#include <Arduino.h>

#include "Arduino_LED_Matrix.h"  // Library for controlling the LED matrix
#include "fonts.h"                // Contains the pixel patterns for each character
ArduinoLEDMatrix matrix;          // Create an LED matrix object

// Frame buffer: A 2D array representing the LED matrix (8 rows x 12 columns)
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


// Setup function: Runs once when the Arduino starts or resets
void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud for debugging
  delay(1500);           // Wait 1.5 seconds for the system to stabilize
  matrix.begin();        // Initialize the LED matrix display
}

// Loop function: Runs continuously after setup()
void loop() {
  // Display numbers 0-9, one at a time
  // 'c' starts at '0' (ASCII 48) and goes to '9' (ASCII 57)
  for (char c = '0'; c <= '9'; c++) {
    clear_frame();           // Clear all LEDs
    add_to_frame(c, 4);      // Draw the character at horizontal position 4 (centered)
    display_frame();         // Send the frame to the LED matrix
    delay(1000);             // Wait 1 second (1000 milliseconds)
  }

  // Display letters A-Z, one at a time
  // 'c' starts at 'A' (ASCII 65) and goes to 'Z' (ASCII 90)
  for (char c = 'A'; c <= 'Z'; c++) {
    clear_frame();           // Clear all LEDs
    add_to_frame(c, 4);      // Draw the character at horizontal position 4 (centered)
    display_frame();         // Send the frame to the LED matrix
    delay(1000);             // Wait 1 second
  }
}

// Clear the frame buffer by setting all LEDs to off (0)
void clear_frame() {
  for (int row = 0; row < 8; row++) {       // Loop through each of the 8 rows
    for (int col = 0; col < 12; col++) {    // Loop through each of the 12 columns
      frame[row][col] = 0;                  // Set LED to off
    }
  }
}

// Send the current frame buffer to the LED matrix display
void display_frame() {
  matrix.renderBitmap(frame, 8, 12);  // Render the 8x12 frame on the matrix
}


// Draw a character at a specific horizontal position in the frame
// Parameters:
//   c   - The character to draw ('0'-'9' or 'A'-'Z')
//   pos - Horizontal position (0-11, where 4 is roughly centered)
void add_to_frame(char c, int pos) {
  int index = -1;  // Index into the fonts array
  
  // Convert character to array index
  // Numbers '0'-'9' map to indices 0-9
  if (c >= '0' && c <= '9')
    index = c - '0';  // Example: '5' (ASCII 53) - '0' (ASCII 48) = 5
  
  // Letters 'A'-'Z' map to indices 10-35
  else if (c >= 'A' && c <= 'Z')
    index = c - 'A' + 10;  // Example: 'C' (ASCII 67) - 'A' (ASCII 65) + 10 = 12
  
  // If character is not supported, print warning and exit
  else {
    Serial.println("WARNING: unsupported character");
    return;
  }

  // Copy the character bitmap into the frame at the specified position
  for (int row = 0; row < 8; row++) {
    // Get the font row and shift it to the desired position
    // Left shift (<<) moves the character pattern horizontally
    uint32_t temp = fonts[index][row] << (7 - pos);
    
    // Set each LED in this row
    for (int col = 0; col < 12; col++) {
      // Extract bit at position 'col' and OR it into the frame
      // The OR operator (|=) turns LEDs on without turning off existing ones
      // Right shift (>>) and & 1 extracts a single bit
      frame[row][col] |= (temp >> (11 - col)) & 1;
    }
  }
}