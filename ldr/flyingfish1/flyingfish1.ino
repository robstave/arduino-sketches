/*
 * Flying Fish LDR Sensor Module with LED Matrix Display
 *
 * Reads analog value from LDR and outputs to Pin 13 (PWM)
 * Displays analog value as bar chart and digital value on LED matrix
 */

#include <LedControl.h>

// LED Matrix pins (adjust these based on your wiring)
const int DIN_PIN = 12;    // Data in
const int CLK_PIN = 11;    // Clock
const int CS_PIN = 10;     // Chip select

// LED Matrix setup
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

const int LDR_ANALOG_PIN = A5;  // LDR analog output
const int LDR_DIGITAL_PIN = A4; // LDR digital threshold output

const int OUTPUT_PIN = 13;      // LED/PWM output pin (PWM capable)

void setup()
{
  // Initialize LED matrix
  lc.shutdown(0, false);  // Wake up the matrix
  lc.setIntensity(0, 8);  // Set brightness (0-15)
  lc.clearDisplay(0);     // Clear the display

  // Set up input pin for digital threshold
  pinMode(LDR_DIGITAL_PIN, INPUT);

  // Set up output pin
  pinMode(OUTPUT_PIN, OUTPUT);

  // Initialize serial for debugging
  Serial.begin(9600);

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
  int pwmValue = map(ldrValue, 0, 1023, 255,0 );

  // Write the PWM value to pin 13
  analogWrite(OUTPUT_PIN, pwmValue);

  // Update LED matrix display
  updateMatrixDisplay(ldrValue, digitalValue);

  // Debug output
  Serial.print("LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(" -> PWM: ");
  Serial.print(pwmValue);
  Serial.print(" | Digital (A4): ");
  Serial.println(digitalValue);

  delay(100); // Small delay for stability
}

// Function to update the LED matrix display
void updateMatrixDisplay(int analogValue, int digitalValue) {
  // Clear the display
  lc.clearDisplay(0);
  
  // Display analog value as bar chart on top row (row 0)
  // Map 0-1023 to 0-7 LEDs
  int barLength = map(analogValue, 0, 1023, 0, 8);
  for (int i = 0; i < barLength; i++) {
    lc.setLed(0, 0, i, true);  // Row 0, columns 0-7
  }
  
  // Display digital value on bottom row (row 7)
  // Fill entire row if digital is 1, leave empty if 0
  for (int i = 0; i < 8; i++) {
    lc.setLed(0, 7, i, digitalValue == 1);
  }
}
