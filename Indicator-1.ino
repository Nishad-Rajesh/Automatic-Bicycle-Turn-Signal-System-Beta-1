#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

// Pin Definitions
const int joyX  = A0;
const int joyY  = A1;

const int leftLED  = 8;  // Left Turn Signal LED
const int rightLED = 9;  // Right Turn Signal LED
const int headLED  = 10; // Headlight LED

// Timing variables for non-blocking blink
unsigned long previousMillis = 0;
const long interval = 350;
bool ledState = LOW;

// Control States
bool headLedOn = false;   // Headlight toggle state
bool autoModeOn = true;   // Tilt sensor activation state

// Edge detection flags for joystick Y-axis toggles
bool yUpLast = false;
bool yDownLast = false;

// Lean thresholds
const float LEAN_THRESHOLD = 3.8; 

void setup() {
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(headLED, OUTPUT);
  
  Serial.begin(9600);
  delay(1000);

  // --- STARTUP SEQUENCE ---
  digitalWrite(leftLED, HIGH);  delay(150); digitalWrite(leftLED, LOW);
  digitalWrite(headLED, HIGH);  delay(150); digitalWrite(headLED, LOW);
  digitalWrite(rightLED, HIGH); delay(150); digitalWrite(rightLED, LOW);

  // Initialize MPU6050
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("ERROR: MPU6050 not detected! Check SDA (A4) and SCL (A5).");
  } else {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    Serial.println("System Initialized: Fixed Right-Lean Blinking Active");
  }
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);

  // --- 1. HEADLIGHT TOGGLE (Push Up and Up again) ---
  bool yUpCurrent = (yValue < 300);
  if (yUpCurrent && !yUpLast) {
    headLedOn = !headLedOn;
    Serial.print("Headlight Toggled: ");
    Serial.println(headLedOn ? "ON" : "OFF");
  }
  yUpLast = yUpCurrent;

  // --- 2. TILT SENSOR TOGGLE (Push Down and Down again) ---
  bool yDownCurrent = (yValue > 900);
  if (yDownCurrent && !yDownLast) {
    autoModeOn = !autoModeOn;
    Serial.print("Tilt Sensor Toggled: ");
    Serial.println(autoModeOn ? "ACTIVE" : "INACTIVE");
  }
  yDownLast = yDownCurrent;

  // --- 3. BLINK TIMER ---
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
  }

  // --- 4. APPLY HEADLIGHT STATE ---
  digitalWrite(headLED, headLedOn ? HIGH : LOW);

  float accelX = a.acceleration.x;

  // --- 5. TURN SIGNAL LOGIC WITH MANUAL OVERRIDE ---
  // Priority 1: Manual Joystick Left/Right overrides everything else instantly
  if (xValue < 300) {
    digitalWrite(leftLED, ledState);
    digitalWrite(rightLED, LOW);
  } 
  else if (xValue > 700) {
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, ledState);
  } 
  // Priority 2: Automatic Lean Detection (Active only if autoModeOn is true)
  else if (autoModeOn) {
    if (accelX > LEAN_THRESHOLD) {
      // Left indicator when X > 3.8
      digitalWrite(leftLED, ledState);
      digitalWrite(rightLED, LOW);
    } 
    else if (accelX < -LEAN_THRESHOLD) {
      // Right indicator when X < -3.8 (FIXED: now correctly blinks rightLED)
      digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, ledState);
    } 
    else {
      // Center deadzone
      digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, LOW);
    }
  } 
  else {
    // Auto Mode is INACTIVE and joystick is centered -> Turn signals OFF
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
  }

  delay(50);
}