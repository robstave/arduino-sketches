/*
  Blink


  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

const int redLight1 = 13;
const int yellowLight1 = 12;
const int greenLight1 = 11;

const int redLight2 = 7;
const int yellowLight2 = 6;
const int greenLight2 = 5;

const int lightDelayShort = 300;
const int lightDelayLong = 899;

enum TrafficLight {
  OFF,
  RED,
  YELLOW,
  GREEN
};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(redLight1, OUTPUT);
  pinMode(yellowLight1, OUTPUT);
  pinMode(greenLight1, OUTPUT);

  pinMode(redLight2, OUTPUT);
  pinMode(yellowLight2, OUTPUT);
  pinMode(greenLight2, OUTPUT);
}

void setAllOff() {
  digitalWrite(redLight1, LOW);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(greenLight1, LOW);

  digitalWrite(redLight2, LOW);
  digitalWrite(yellowLight2, LOW);
  digitalWrite(greenLight2, LOW);
}

void setLights(TrafficLight light1, TrafficLight light2) {

  setAllOff();
  switch (light1) {

    case RED:
      digitalWrite(redLight1, HIGH);

      break;

    case YELLOW:
      digitalWrite(yellowLight1, HIGH);

      break;

    case GREEN:
      digitalWrite(greenLight1, HIGH);

      break;

    case OFF:

      // All lights are already off
      break;
    default:
      //
      break;
  }


  switch (light2) {

    case RED:
      digitalWrite(redLight2, HIGH);

      break;

    case YELLOW:
      digitalWrite(yellowLight2, HIGH);

      break;

    case GREEN:
      digitalWrite(greenLight2, HIGH);

      break;

    case OFF:

      // All lights are already off
      break;
    default:
      //
      break;
  }
}

void loop() {
  setLights(RED, GREEN);
  delay(lightDelayLong);

  setLights(RED, YELLOW);
  delay(lightDelayShort);

  setLights(RED, RED);
  delay(lightDelayShort);

  setLights(GREEN, RED );
  delay(lightDelayLong);
  setLights(YELLOW, RED);
  delay(lightDelayShort);

  setLights(RED, RED);
  delay(lightDelayShort);
}
