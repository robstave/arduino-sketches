 /*
 * Flying Fish LDR Sensor Module
 *
 * Reads analog value from LDR and outputs to Pin 13 (PWM)
 */

const int LDR_ANALOG_PIN = A5;  // LDR analog output
const int LDR_DIGITAL_PIN = A4; // LDR digital threshold output
 
const int OUTPUT_PIN = 13;      // LED/PWM output pin (PWM capable)

void setup()
{
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

  // Debug output
  Serial.print("LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(" -> PWM: ");
  Serial.print(pwmValue);
  Serial.print(" | Digital (A4): ");
  Serial.println(digitalValue);

  delay(100); // Small delay for stability
}
