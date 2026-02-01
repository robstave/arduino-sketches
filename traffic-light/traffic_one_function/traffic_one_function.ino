 


const int redLight1 = 13;
const int yellowLight1 = 12;
const int greenLight1 = 11;
const int lightDelayShort = 300;
const int lightDelayLong = 899;

enum TrafficLight
{
  OFF,
  RED,
  YELLOW,
  GREEN
};

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(redLight1, OUTPUT);
  pinMode(yellowLight1, OUTPUT);
  pinMode(greenLight1, OUTPUT);
}

void setLight1(TrafficLight light)
{

  switch (light)
  {

    digitalWrite(redLight1, LOW);
    digitalWrite(yellowLight1, LOW);
    digitalWrite(greenLight1, LOW);

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
}

void loop()
{

  // Turn on red light
  setLight1(RED);
  delay(lightDelayLong);

  // Turn on green light

  setLight1(GREEN);
  delay(lightDelayLong);

  // Turn on yellow light

  setLight1(YELLOW);
  delay(lightDelayShort);
}
