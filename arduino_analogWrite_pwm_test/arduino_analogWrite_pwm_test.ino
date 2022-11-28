
int led = 9;         // the PWM pin the LED is attached to
int brightness = 0;  // how bright the LED is
int fadeAmount = 1;  // how many points to fade the LED by

// the setup function runs once when you press reset or power the board
void setup() {
  #define SERIALP Serial // different Arduino have variuos serial ports, so control which one we use
  // Open serial communications and wait for port to open:
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

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // declare led pin set above to be an output:
  pinMode(led, OUTPUT);

  // test some extremes at start up
  analogWrite(led, 255);
  delay(3000);
  analogWrite(led, 0);
  delay(3000);
  analogWrite(led, 1);
  delay(3000);
}

// the loop function runs over and over again forever
void loop() {
  if (fadeAmount > 0) { // turn led on if pwm brightness increasing
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  }

  // change the brightness to ramp up and down:
  brightness = brightness + fadeAmount;

  // set the brightness of led pin:
  analogWrite(led, brightness);

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    // sample prints for debugging, comment out if not needed.
    //SERIALP.print("brightness: ");
    //SERIALP.print(brightness);
    //SERIALP.print("  fadeAmount: ");
    //SERIALP.println(fadeAmount);
    delay(1000); // stay at the top and bottom for a bit
  }

  // wait for 30 milliseconds to see the dimming effect
  delay(20);
}
