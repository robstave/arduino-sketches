 
 

const int redLight1 = 13;
const int yellowLight1 = 12;
const int greenLight1 = 11;
const int lightDelayShort = 300;
const int lightDelayLong = 899;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(redLight1, OUTPUT);
  pinMode(yellowLight1, OUTPUT);
  pinMode(greenLight1, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  digitalWrite(greenLight1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(yellowLight1, LOW);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(redLight1, HIGH);    // turn the LED on (HIGH is the voltage level)
  
  delay(lightDelayLong);

  digitalWrite(greenLight1, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(yellowLight1, LOW);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(redLight1, LOW);     // turn the LED on (HIGH is the voltage level)

  delay(lightDelayLong);  // wait for a second

  digitalWrite(greenLight1, LOW);    // turn the LED on (HIGH is the voltage level)
  digitalWrite(yellowLight1, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(redLight1, LOW);      // turn the LED on (HIGH is the voltage level)
  delay(lightDelayShort);            // wait for a second
                                     // wait for a second
}
