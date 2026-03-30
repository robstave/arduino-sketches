 /*
 * Flying Fish LDR Sensor Module
 *
 * Reads analog value from LDR and outputs to Pin 13 (PWM)
 * Also displays values on the Arduino UNO R4 WiFi LED Matrix
 */

#include "Arduino_LED_Matrix.h"

const int LDR_ANALOG_PIN = A5;  // LDR analog output
const int LDR_DIGITAL_PIN = A4; // LDR digital threshold output
 
const int OUTPUT_PIN = 13;      // LED/PWM output pin (PWM capable)

ArduinoLEDMatrix matrix;
uint8_t frame[8][12];

void setup()
{
  // Set up input pin for digital threshold
  pinMode(LDR_DIGITAL_PIN, INPUT);

  // Set up output pin
  pinMode(OUTPUT_PIN, OUTPUT);

  // Initialize serial for debugging
  Serial.begin(9600);

  // Initialize LED Matrix
  matrix.begin();

  // Give the module time to stabilize
  delay(100);
}

void loop()
{
  // Read the analog value from the LDR (0-1023)
  int ldrValue = analogRead(LDR_ANALOG_PIN);
  
  // Read the digital threshold value from the LDR
  int digitalValue = !digitalRead(LDR_DIGITAL_PIN);

  // Map the value to PWM range (0-255)
  int pwmValue = map(ldrValue, 0, 1023, 255, 0);

  // Write the PWM value to pin 13
  analogWrite(OUTPUT_PIN, pwmValue);

  // Update LED Matrix
  updateMatrix(ldrValue, digitalValue);

  // Debug output
  Serial.print("LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(" -> PWM: ");
  Serial.print(pwmValue);
  Serial.print(" | Digital (A4): ");
  Serial.println(digitalValue);

  delay(100); // Small delay for stability
}

void updateMatrix(int analogVal, int digitalVal) {
  // Clear frame
  memset(frame, 0, sizeof(frame));

  // --- Labels in cols 0-3, col 4 is spacer ---
  //
  // "A" label for analog section (rows 0-3):
  //   _xx_
  //   x__x
  //   xxxx
  //   x__x
  const uint8_t labelA[4][4] = {
    {0,1,1,0},
    {1,0,0,1},
    {1,1,1,1},
    {1,0,0,1}
  };

  // "D" label for digital section (rows 4-7):
  //   xx__
  //   x__x
  //   x__x
  //   xx__
  const uint8_t labelD[4][4] = {
    {1,1,0,0},
    {1,0,0,1},
    {1,0,0,1},
    {1,1,0,0}
  };

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      frame[r][c]     = labelA[r][c];
      frame[r + 4][c] = labelD[r][c];
    }
  }

  // --- Bars in cols 5-11 (7 columns wide, 2 rows tall) ---

  // Analog bar: rows 1-2, more light = wider bar
  int analogBar = map(analogVal, 0, 1023, 7, 0);
  for (int r = 1; r <= 2; r++) {
    for (int c = 0; c < analogBar; c++) {
      frame[r][5 + c] = 1;
    }
  }

  // Digital bar: rows 5-6, full bar if threshold crossed, empty if not
  if (digitalVal == 1) {
    for (int r = 5; r <= 6; r++) {
      for (int c = 5; c < 12; c++) {
        frame[r][c] = 1;
      }
    }
  }

  matrix.renderBitmap(frame, 8, 12);
}

