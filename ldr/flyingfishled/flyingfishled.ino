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
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 12; c++) {
      frame[r][c] = 0;
    }
  }

  // Top part: Bar chart for Analog Value
  // Map 0-1023 to 0-12 columns
  int barWidth = map(analogVal, 0, 1023, 0, 12);
  
  // Draw bar on top 4 rows (0-3)
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < barWidth; c++) {
      frame[r][c] = 1;
    }
  }

  // Bottom part: Digital Value indicator
  // If digitalVal is 1 (active), fill bottom 4 rows (4-7)
  if (digitalVal == 1) {
    for (int r = 4; r < 8; r++) {
      for (int c = 0; c < 12; c++) {
        frame[r][c] = 1;
      }
    }
  } else {
    // Optional: Draw an outline or just leave empty for 0
    // Let's leave it empty as per "empty or filled bar" request
  }

  matrix.renderBitmap(frame, 8, 12);
}

