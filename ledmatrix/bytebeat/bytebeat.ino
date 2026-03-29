/*
 * Bytebeat Visualizer
 * For Arduino UNO R4 LED Matrix (8x12)
 *
 * Bytebeat: a single math expression using a time counter 't' produces
 * a uint8_t value each tick. Originally used for raw 8-bit audio synthesis,
 * here we visualize the output on the LED matrix.
 *
 * Each tick:
 *   - Evaluate the current formula at time t -> get a byte (0-255)
 *   - Each of the 8 bits maps to one row (bit 7 = top, bit 0 = bottom)
 *   - Shift the display left by one column
 *   - Draw the new byte on the rightmost column
 *   - Increment t
 *
 * Joystick:
 *   A0 - X-axis: push left/right to cycle through 8 bytebeat formulas
 *   A1 - Y-axis: adjust scroll speed (slow to fast)
 *   A2 - Button: reset t to 0 (restart current pattern)
 */

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

const int COLS = 12;
const int ROWS = 8;

const int PIN_X   = A0;
const int PIN_Y   = A1;
const int PIN_BTN = A2;

uint8_t frame[ROWS][COLS];

// Bytebeat time counter
unsigned long t = 0;

// Current formula index
int currentFormula = 0;
const int NUM_FORMULAS = 8;

// Joystick zone tracking for formula switching
int lastZone = 1; // 0=left, 1=center, 2=right

bool lastBtn = HIGH;

// Scroll speed (ms per column)
int scrollDelay = 40;

// Function prototypes
uint8_t bytebeat(unsigned long t);

// Evaluate the current bytebeat formula
uint8_t bytebeat(unsigned long t) {
  switch (currentFormula) {
    case 0:
      // "Crowd" - Viznut's original. Grinding, rhythmic, iconic.
      return t * (((t >> 12) | (t >> 8)) & (63 & (t >> 4)));

    case 1:
      // "Sierpinski Harmony" - Fractal triangles, two interleaved melodies.
      return (t * 5 & t >> 7) | (t * 3 & t >> 10);

    case 2:
      // "42 Melody" - Surprisingly musical from a tiny expression.
      return t * (42 & t >> 10);

    case 3:
      // "Tejeez" - Smooth descending cascade with volume envelope.
      return (t * (t >> 5 | t >> 8)) >> (t >> 16);

    case 4:
      // "Chip-tune" - Old-school video game vibes.
      return t * ((t >> 9 | t >> 13) & 25 & t >> 6);

    case 5:
      // "Three-voice" - Three layered voices, algorithmic choir.
      return (t * 9 & t >> 4 | t * 5 & t >> 7 | t * 3 & t / 1024) - 1;

    case 6:
      // "FM Madness" - Clean 6-bit patterns, parabolic waveform.
      return t * t >> 8 & 63;

    case 7:
      // "Lost in Space" - Spacey, ambient, hypnotic.
      return ((t * (t >> 8 | t >> 9) & 46 & t >> 8)) ^ (t & t >> 13 | t >> 6);

    default:
      return t;
  }
}

void setup() {
  Serial.begin(115200);
  matrix.begin();

  pinMode(PIN_X, INPUT);
  pinMode(PIN_Y, INPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);

  memset(frame, 0, sizeof(frame));
}

void loop() {
  // --- Read inputs ---
  int joyX = analogRead(PIN_X);
  int joyY = analogRead(PIN_Y);
  bool btn = digitalRead(PIN_BTN);

  // Button: reset t (restart pattern from the beginning)
  if (btn == LOW && lastBtn == HIGH) {
    t = 0;
    memset(frame, 0, sizeof(frame));
    delay(50);
  }
  lastBtn = btn;

  // Joystick X: change formula when pushed left or right
  // Uses "zone" detection so you get one switch per push
  int zone;
  if (joyX < 300) {
    zone = 0; // left
  } else if (joyX > 723) {
    zone = 2; // right
  } else {
    zone = 1; // center
  }

  if (zone != lastZone) {
    if (zone == 0 && lastZone == 1) {
      // Pushed left -> previous formula
      currentFormula = (currentFormula - 1 + NUM_FORMULAS) % NUM_FORMULAS;
      t = 0;
      memset(frame, 0, sizeof(frame));
    } else if (zone == 2 && lastZone == 1) {
      // Pushed right -> next formula
      currentFormula = (currentFormula + 1) % NUM_FORMULAS;
      t = 0;
      memset(frame, 0, sizeof(frame));
    }
    lastZone = zone;
  }

  // Joystick Y: adjust scroll speed
  scrollDelay = map(joyY, 0, 1023, 80, 10);

  // --- Compute bytebeat value ---
  uint8_t val = bytebeat(t);

  // --- Scroll frame left by one column ---
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS - 1; c++) {
      frame[r][c] = frame[r][c + 1];
    }
  }

  // --- Draw new byte as rightmost column ---
  // Bit 7 (MSB) = top row, bit 0 (LSB) = bottom row
  for (int r = 0; r < ROWS; r++) {
    frame[r][COLS - 1] = (val >> (7 - r)) & 1;
  }

  // --- Render ---
  matrix.renderBitmap(frame, ROWS, COLS);

  t++;
  delay(scrollDelay);
}
