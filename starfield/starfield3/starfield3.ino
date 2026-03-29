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

const int NUM_STARS = 7;
Star stars[NUM_STARS];

struct Laser {
  float x;
  float y;
  float z;
  bool active;
};

const int MAX_LASERS = 4; // Max number of lasers on screen at once
Laser lasers[MAX_LASERS];

// Function prototypes
void display_frame();
void clear_frame();
void resetStar(int i);
void fireLaser();
void updateLasers(float turnX, float turnY);

// Speed of the star field
float speed = 0.1; // Adjust for faster/slower movement

// Joystick pins
const int JOYSTICK_X_PIN = A0;
const int JOYSTICK_Y_PIN = A1;
const int JOYSTICK_BTN_PIN = A2;

bool lastButtonState = HIGH; // Assuming pull-up (LOW when pressed)

void setup() {
  Serial.begin(115200);
  // Default resolution is 10-bit (0-1023)
  // analogReadResolution(10); 
  
  pinMode(JOYSTICK_X_PIN, INPUT);
  pinMode(JOYSTICK_Y_PIN, INPUT);
  pinMode(JOYSTICK_BTN_PIN, INPUT_PULLUP);

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
  
  // Read joystick values (0-1023)
  // Center is ~512
  int joyX = analogRead(JOYSTICK_X_PIN);
  int joyY = analogRead(JOYSTICK_Y_PIN);
  
  // Read button
  bool buttonState = digitalRead(JOYSTICK_BTN_PIN);
  
  // Fire on press (LOW) if previously released (HIGH)
  if (buttonState == LOW && lastButtonState == HIGH) {
    fireLaser();
  }
  lastButtonState = buttonState;

  // Calculate turn speed based on joystick displacement from center
  // Adjust divisor to control sensitivity (higher number = slower turn)
  // X axis: 0-1023, center ~512.
  // Y axis: 0-1023, center ~512.
  // Divide by 4000.0 gives range approx -0.12 to 0.12 per frame
  float turnX = (joyX - 512) / 4000.0; 
  float turnY = (joyY - 512) / 4000.0;
  
  updateLasers(turnX, turnY);

  for (int i = 0; i < NUM_STARS; i++) {
    // Move star closer
    stars[i].z -= speed;
    
    // Apply turn effect to existing stars
    // If we turn right (positive turnX), stars move left (pan camera right)
    stars[i].x -= turnX;
    stars[i].y -= turnY;
    
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

void fireLaser() {
  // Find two empty slots for twin lasers
  // We need to find 2 slots to fire a pair.
  int slotsFound = 0;
  int indices[2];
  
  for (int i = 0; i < MAX_LASERS; i++) {
    if (!lasers[i].active) {
      indices[slotsFound++] = i;
      if (slotsFound == 2) break;
    }
  }

  if (slotsFound == 2) {
    // Left canon
    int idx1 = indices[0];
    lasers[idx1].x = -3.0; // Left of center
    lasers[idx1].y = 1.5;  // Just below center in world space
    lasers[idx1].z = 1.0;  // Start slightly in front
    lasers[idx1].active = true;

    // Right canon
    int idx2 = indices[1];
    lasers[idx2].x = 3.0; // Right of center
    lasers[idx2].y = 1.5;
    lasers[idx2].z = 1.0;
    lasers[idx2].active = true;
  }
}

void updateLasers(float turnX, float turnY) {
  for (int i = 0; i < MAX_LASERS; i++) {
    if (!lasers[i].active) continue;

    // Move laser forward (away from camera)
    lasers[i].z += speed * 3.0; // Lasers move faster than ship speed

    // Apply turn shift (opposite to turn direction)
    // As we turn, existing lasers appear to move sideways
    lasers[i].x -= turnX;
    lasers[i].y -= turnY;
    
    // Project 3D coordinates to 2D screen space
    float sx = (lasers[i].x / lasers[i].z) * 1.5 + 6; 
    float sy = (lasers[i].y / lasers[i].z) * 1.5 + 4;
    
    int pixelX = (int)sx;
    int pixelY = (int)sy;

    // Check if laser is within screen bounds
    if (pixelX >= 0 && pixelX < 12 && pixelY >= 0 && pixelY < 8) {
      frame[pixelY][pixelX] = 1; 
    }

    // Deactivate if too far away
    if (lasers[i].z > 15.0) {
      lasers[i].active = false;
    }
  }
}
