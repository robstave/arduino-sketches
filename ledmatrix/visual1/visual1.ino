/*
 * Matrix Digital Rain
 * For Arduino UNO R4 LED Matrix (8x12)
 *
 * Columns of pixels fall from top to bottom like the Matrix movie effect.
 * The "fade trail" is created by pixel persistence:
 *   - The matrix only supports ON or OFF per pixel (no PWM).
 *   - Each pixel has a brightness counter that decays each tick.
 *   - Any pixel with brightness > 0 is shown as ON.
 *   - The head of the drop sets brightness to max.
 *   - As the head moves down, trailing pixels count down and wink
 *     out one by one, creating the illusion of a fading tail.
 *
 * Joystick:
 *   A0 - X-axis: "wind" (lean rain left/right)
 *   A1 - not used (could add speed)
 *   A2 - Button: freeze/unfreeze rain
 */

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// --- Configuration ---
const int COLS = 12;
const int ROWS = 8;

const int PIN_X   = A0;
const int PIN_BTN = A2;

// Trail length: the head sets a pixel to MAX_BRIGHT,
// then it decays by 1 each tick. Pixel is ON while > 0.
const int MAX_BRIGHT = 5;

// Delay between logic update ticks (animation speed)
const int TICK_MS = 140;

// --- State ---
uint8_t bright[ROWS][COLS]; // Per-pixel brightness 0-3

// Each column has a "drop" - the falling head position
struct Drop {
  int  head;      // Current row of the bright head (-1 = not active)
  int  length;    // Trail length before it fully fades out
  int  countdown; // Ticks until next move
  int  speed;     // Ticks between moves (lower = faster)
};

Drop drops[COLS];

bool frozen = false;
bool lastBtn = HIGH;

// Binary frame for rendering
uint8_t outFrame[ROWS][COLS];

void setup() {
  Serial.begin(115200);
  matrix.begin();

  pinMode(PIN_X,   INPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);

  // Initialise drops
  for (int c = 0; c < COLS; c++) {
    drops[c].head      = -1; // inactive, will spawn randomly
    drops[c].speed     = random(3, 8);
    drops[c].countdown = random(0, 15); // stagger start times
    drops[c].length    = random(3, 7);
  }

  memset(bright, 0, sizeof(bright));
}

void loop() {
  unsigned long tickStart = millis();

  // --- Read inputs ---
  int joyX  = analogRead(PIN_X);
  bool btn  = digitalRead(PIN_BTN);

  // Toggle freeze on button press
  if (btn == LOW && lastBtn == HIGH) {
    frozen = !frozen;
    delay(50); // debounce
  }
  lastBtn = btn;

  // Wind: joystick X offset applied to new drop spawning column
  // Represents diagonal lean: -2 to +2 column lean
  int wind = map(joyX, 0, 1023, -2, 2);

  // --- Logic tick (only if not frozen) ---
  if (!frozen) {
    // Fade the brightness buffer (decay all pixels each tick)
    for (int r = 0; r < ROWS; r++) {
      for (int c = 0; c < COLS; c++) {
        if (bright[r][c] > 0) {
          bright[r][c]--;
        }
      }
    }

    // Advance each drop
    for (int c = 0; c < COLS; c++) {
      drops[c].countdown--;
      if (drops[c].countdown <= 0) {
        drops[c].countdown = drops[c].speed;

        if (drops[c].head < 0) {
          // Inactive: chance to spawn a new drop
          if (random(5) == 0) {
            drops[c].head      = 0;
            drops[c].length    = random(3, 7);
            drops[c].speed     = random(3, 8);
          }
        } else {
          // Move head down one row
          drops[c].head++;

          if (drops[c].head >= ROWS + drops[c].length) {
            // Drop has fully left the screen
            drops[c].head = -1;
          }
        }
      }

      // Paint the head pixel with max brightness (with wind lean)
      if (drops[c].head >= 0 && drops[c].head < ROWS) {
        int paintCol = constrain(c + wind, 0, COLS - 1);
        bright[drops[c].head][paintCol] = MAX_BRIGHT;
      }
    }
  }

  // --- Render single frame ---
  // Any pixel with brightness > 0 is ON. The trail "fades" by
  // pixels winking out one by one as their counters reach zero.
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      outFrame[r][c] = (bright[r][c] > 0) ? 1 : 0;
    }
  }
  matrix.renderBitmap(outFrame, ROWS, COLS);

  // Wait remainder of tick
  unsigned long elapsed = millis() - tickStart;
  if (elapsed < (unsigned long)TICK_MS) {
    delay(TICK_MS - elapsed);
  }
}
