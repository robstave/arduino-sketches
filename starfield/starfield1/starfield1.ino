/*
 * Starfield Animation
 * For Arduino UNO R4 LED Matrix (8x12)
 * 
 * Simulates a flight through space with stars radiating from the center.
 */

#include <Arduino.h>
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

uint8_t frame[8][12];

struct Star {
  float x;
  float y;
  float z;
};

const int NUM_STARS = 15;
Star stars[NUM_STARS];

// Function prototypes
void display_frame();
void clear_frame();
void resetStar(int i);

// Speed of the star field
float speed = 0.15; // Adjust for faster/slower movement

void setup() {
  Serial.begin(115200);
  delay(1500);
  matrix.begin();
  
  // Initialize stars with random positions
  for (int i = 0; i < NUM_STARS; i++) {
    resetStar(i);
    // Give them random initial Z so they don't all start at the back
    stars[i].z = random(100) / 10.0; 
  }
}

void loop() {
  clear_frame();
  
  for (int i = 0; i < NUM_STARS; i++) {
    // Move star closer
    stars[i].z -= speed;
    
    // If star hits the "screen" or goes behind us, reset it
    if (stars[i].z <= 0.1) {
      resetStar(i);
    }
    
    // Project 3D coordinates to 2D screen space
    // Center is approximately (6, 4)
    // The divisor 1.5 helps scale the field of view
    float sx = (stars[i].x / stars[i].z) * 1.5 + 6; 
    float sy = (stars[i].y / stars[i].z) * 1.5 + 4;
    
    int pixelX = (int)sx;
    int pixelY = (int)sy;
    
    // Check if star is within screen bounds
    if (pixelX >= 0 && pixelX < 12 && pixelY >= 0 && pixelY < 8) {
      frame[pixelY][pixelX] = 1; // Draw star
    } else {
      // Optional: Reset stars that go off screen to keep density constant
      // But letting them flow out looks more natural usually.
      // If Z is still high but it went off screen, we leave it be until Z gets low (or reset it).
      // For a continuous flow, usually you just let them drift out.
      // However, if we only reset on z <= 0.1, we might run out of visible stars if they go wide.
      // Let's stick to z-reset for 'warp' feel. 
    }
  }
  
  display_frame();
  delay(30); // Frame rate control
}

void resetStar(int i) {
  // Random X and Y in a range centered around 0
  stars[i].x = random(200) / 10.0 - 10.0; // -10.0 to 10.0
  stars[i].y = random(160) / 10.0 - 8.0;  // -8.0 to 8.0
  stars[i].z = 10.0; // Start far away
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
