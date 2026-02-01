#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo


// Sweep settings
const int SWEEP_TIME_MS = 3000;  // 3 seconds for full sweep (0 to 180 or 180 to 0)
const int STEP_DELAY = 15;       // delay between each step in ms
const int STEPS = SWEEP_TIME_MS / STEP_DELAY;  // number of steps per sweep

void setup() {
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
    myservo2.attach(10);  // attaches the servo on pin 9 to the servo object

}

void loop() {
  // Sweep from 0 to 180 degrees over 3 seconds
  for (int i = 0; i <= STEPS; i++) {
    int pos = map(i, 0, STEPS, 0, 180);
    myservo1.write(pos);
        myservo2.write(pos);

    delay(STEP_DELAY);
  }

  // Sweep from 180 to 0 degrees over 3 seconds
  for (int i = 0; i <= STEPS; i++) {
    int pos = map(i, 0, STEPS, 180, 0);
    myservo1.write(pos);
            myservo2.write(pos);

    delay(STEP_DELAY);
  }
}