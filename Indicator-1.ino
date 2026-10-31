const int joyX = A0;   // X-axis of joystick
const int leftLED = 8;  // Left turn signal LED (LF/LB)
const int rightLED = 9; // Right turn signal LED (RF/RB)

// Timing variables for the blink effect
unsigned long previousMillis = 0;
const long interval = 350; // Speed of the blink (lower = faster)
bool ledState = LOW;

void setup() {
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(joyX); // Reads 0 (left) to 1023 (right); center is ~500

  // Handle the blinking timer independently so the joystick stays responsive
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState; // Toggle between HIGH and LOW
  }

  // Check joystick position
  if (xValue < 300) {
    // Pushed Left: Blink the Left LED, keep Right off
    digitalWrite(leftLED, ledState);
    digitalWrite(rightLED, LOW);
  } 
  else if (xValue > 700) {
    // Pushed Right: Keep Left off, blink the Right LED
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, ledState);
  } 
  else {
    // Centered: Turn both off completely
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
    ledState = LOW; 
  }
}