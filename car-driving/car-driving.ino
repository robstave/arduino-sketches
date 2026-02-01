/*
 * Car Driving LED Matrix Animation
 * For Arduino UNO R4 LED Matrix (8x12)
 * 
 * Displays a car that shifts up and down to simulate driving motion
 */

#include <Arduino.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

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

// Car sprite - 8 rows x 10 columns (side view of a car)
// The car is designed to fit within the 8x12 matrix
const uint8_t car[5][10] = {
  { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },  // roof
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },  // windows
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // body top
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // body bottom  
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0 }   // wheels
};

const int CAR_HEIGHT = 5;
const int CAR_WIDTH = 10;

void setup() {
  Serial.begin(115200);
  delay(1500);
  matrix.begin();
}

void loop() {
  // Animate car bouncing up and down to simulate driving
  // Position 1: car slightly up
  clear_frame();
  draw_car(1, 1);  // offset Y = 1 (up position)
  display_frame();
  delay(150);

  // Position 2: car slightly down  
  clear_frame();
  draw_car(1, 2);  // offset Y = 2 (down position)
  display_frame();
  delay(150);
}

void clear_frame() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 12; col++) {
      frame[row][col] = 0;
    }
  }
}

void display_frame() {
  matrix.renderBitmap(frame, 8, 12);
}

// Draw the car at specified position
// offsetX: horizontal position (0-2 to keep car visible)
// offsetY: vertical position (0-3 to keep car visible)
void draw_car(int offsetX, int offsetY) {
  for (int row = 0; row < CAR_HEIGHT; row++) {
    for (int col = 0; col < CAR_WIDTH; col++) {
      int targetRow = row + offsetY;
      int targetCol = col + offsetX;
      
      // Make sure we're within the frame bounds
      if (targetRow >= 0 && targetRow < 8 && targetCol >= 0 && targetCol < 12) {
        frame[targetRow][targetCol] = car[row][col];
      }
    }
  }
}
