/*
 * Eyeball Animation
 * For Arduino UNO R4 LED Matrix (8x12)
 * 
 * Simulates an eyeball that looks around based on joystick input.
 * Button press (A2) triggers a blink.
 */
#include <Arduino.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Joystick configuration
const int PIN_X = A0;
const int PIN_Y = A1;
const int PIN_BTN = A2; // Button for blink

// Frame buffer
uint8_t frame[8][12];

// Eye parameters
// The pupil is a dark spot on a lit eye.
// Pupil size: 2x2
// Eye shape defined by a mask or logic.

// Function prototypes
void drawEye(int px, int py, float openness);
void blinkEye(int px, int py);
void clearFrame();

void setup() {
  Serial.begin(115200);
  matrix.begin();
  
  pinMode(PIN_X, INPUT);
  pinMode(PIN_Y, INPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);
}

void loop() {
  // Read joystick and calculate intended position first
  int joyX = analogRead(PIN_X);
  int joyY = analogRead(PIN_Y);
  
  // Map joystick (0-1023) to pupil position
  // Pupil is 2x2.
  // X range: 2 to 8 (so 2x2 pupil fits within 12 width with some sclera margin)
  // Y range: 1 to 5 (fits within 8 height)
  
  // Invert mapping as needed based on joystick orientation
  // Assuming 0 is left/up
  // map(value, fromLow, fromHigh, toLow, toHigh)
  int pupilX = map(joyX, 0, 1023, 2, 8); // Swap 2, 8 if direction is wrong
  int pupilY = map(joyY, 0, 1023, 1, 5); 
  
  // Constrain just in case
  pupilX = constrain(pupilX, 2, 8);
  pupilY = constrain(pupilY, 1, 5);

  // Check for blink
  if (digitalRead(PIN_BTN) == LOW) {
    blinkEye(pupilX, pupilY);
    // Wait for button release
    delay(200); 
    while(digitalRead(PIN_BTN) == LOW); 
  } else {
    // Normal operation: Look around
    drawEye(pupilX, pupilY, 1.0); // 1.0 = fully open
  }
  
  delay(30); // 30fps-ish
}

// Draw the eye with pupil at (px, py) and openness factor (0.0 closed - 1.0 open)
void drawEye(int px, int py, float openness) {
  clearFrame();
  
  // 1. Draw the Sclera (White of the eye)
  // We'll approximate an oval shape
  // Rows 0 and 7 are trimmed to make it rounder
  // Cols 0, 11 trimmed
  
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 12; x++) {
      // Basic oval logic approximation
      bool isSclera = true;
      
      // Corners transparent
      if ((y == 0 || y == 7) && (x < 2 || x > 9)) isSclera = false;
      if ((y == 1 || y == 6) && (x < 1 || x > 10)) isSclera = false;
      
      // Eyelids (based on openness)
      // Height is 8. Center is 3.5.
      // If openness is 0, only center row might be visible? Or none..
      // Calculate max Y distance from center allowed
      float maxDist = 4.0 * openness;
      if (abs(y - 3.5) > maxDist) isSclera = false;

      if (isSclera) {
        frame[y][x] = 1;
      }
    }
  }
  
  // 2. Draw the Pupil (Black 2x2 square) ONLY if eye is open enough
  if (openness > 0.2) {
    // Pupil occupies (px, py), (px+1, py), (px, py+1), (px+1, py+1)
    if(px >= 0 && px < 11 && py >= 0 && py < 7) {
       frame[py][px] = 0;
       frame[py][px+1] = 0;
       frame[py+1][px] = 0;
       frame[py+1][px+1] = 0;
       
       // Add slight shine to pupil? (optional, maybe one pixel in the corner of the black square is white?)
       // Let's keep it simple black for now.
    }
  }
  
  matrix.renderBitmap(frame, 8, 12);
}

void blinkEye(int px, int py) {
  // Animation: Close
  for (float open = 1.0; open >= 0.0; open -= 0.15) {
     drawEye(px, py, open);
     delay(40); // Slower blink is more visible
  }
  
  // Closed for a moment
  drawEye(px, py, 0.0);
  delay(150);
  
  // Animation: Open
  for (float open = 0.0; open <= 1.0; open += 0.15) {
     drawEye(px, py, open);
     delay(40);
  }
}

void clearFrame() {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 12; j++)
      frame[i][j] = 0;
}
