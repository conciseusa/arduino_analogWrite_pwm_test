
#define BUTTON 7     // the input pin the optional control button is attached to
#define AUTO_CYCLE_PIN 8  // pull low to use button to set brightness
#define PWM 9        // the PWM pin the LED is attached to
int brightness = 5;  // how bright the LED is, start off dim
int fadeAmount = 1;  // how many points to fade the LED by
int fadeDelay = 20;
int prev_button_state = HIGH;

// the setup function runs once when you press reset or power the board
void setup() {
  #define SERIALP Serial // different Arduino have variuos serial ports, so control which one we use
  // #define USE_SERIAL1 1
  // #undef SERIALP
  // #define SERIALP Serial1
  // examples of auto setting SERIALP: https://github.com/conciseusa/arduino-rtc-json-data-logger

  // Open serial communications and wait for port to open, uncomment to use.
/*
#if defined(USE_SERIAL1)
  Serial1.begin(9600);
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#else
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif
*/

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(AUTO_CYCLE_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
  pinMode(PWM, OUTPUT); // declare pwm pin set above to be an output.

  // test some extremes at start up, comment out if not wanted.
  analogWrite(PWM, 255);
  delay(2000);
  analogWrite(PWM, 0);
  delay(2000);
  analogWrite(PWM, 1);
  delay(2000);
}

void loop() { // the loop function runs over and over again forever
  if ((digitalRead(AUTO_CYCLE_PIN) == LOW) && (digitalRead(BUTTON) == LOW) && (digitalRead(BUTTON) != prev_button_state)) {
    // if button was just pressed, toggle fade, but point inward if at extremes
    if (brightness <= 0) {
      fadeAmount = 1;
    } else if (brightness >= 255) {
      fadeAmount = -1;
    } else {
      fadeAmount = -fadeAmount;
    }
  }
  prev_button_state = digitalRead(BUTTON);

  if (fadeAmount > 0) { // turn led on if pwm brightness increasing
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  }

  if ((digitalRead(AUTO_CYCLE_PIN) == HIGH) || (digitalRead(BUTTON) == LOW)) { // if in auto mode or button pressed
    brightness = brightness + fadeAmount; // change the brightness to ramp up and down
  }

  analogWrite(PWM, brightness); // set the level of pwm pin:

  // reverse the direction of the fading at the ends of the auto fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    // sample prints for debugging, comment out if not needed.
    //SERIALP.print("brightness: ");
    //SERIALP.print(brightness);
    //SERIALP.print("  fadeAmount: ");
    //SERIALP.println(fadeAmount);
    delay(1000); // stay at the top and bottom for a bit
  }

  // wait X milliseconds to see the dimming effect
  if (brightness < 5) {
    delay(fadeDelay * 4); // slow down at the very dim end
  } else {
    delay(fadeDelay);
  }
}
