#include <Arduino.h>
#include <Servo.h>
#include <IRremote.h>

// Pin Definitions
const int IR_RECEIVER_PIN = 2; // Pin for the TSOP1838
const int EN1 = 6;             // Enable pin for Motor 1 (PWM, Timer1)
const int IN1 = 8;             // Input 1 for Motor 1
const int IN2 = 7;             // Input 2 for Motor 1
const int SERVO_PIN = 3;       // Pin for the Servo (Using ServoTimer2)

// Create ServoTimer2 object
Servo myServo;

// Motor and Servo state variables
int motorSpeed = 0;            // Current motor speed (PWM value)
bool motorOn = false;          // Motor on/off state
bool motorDirection = true;    // Motor direction: true = forward, false = backward
int servoPosition = 90;        // Current servo position (neutral = 90 degrees)

// Function Declarations
void toggleMotor();
void increaseSpeed();
void decreaseSpeed();
void switchDirection();
void setMotorDirection(bool forward);
void moveServoLeft();
void moveServoRight();

void setup() {
  // Motor driver setup
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  analogWrite(EN1, 0);          // Motor initially stopped
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  // Servo setup using ServoTimer2
  myServo.attach(SERVO_PIN);
  myServo.write(90); // Set servo to neutral position

  // IR receiver setup
  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);

  // Serial setup for debugging
  Serial.begin(9600);
  Serial.println("=== System Initialized ===");
  Serial.println("IR Receiver, Motor Driver, and Servo ready...");
}

void loop() {
  // Check if an IR signal has been received
  if (IrReceiver.decode()) {
    unsigned long receivedCode = IrReceiver.decodedIRData.decodedRawData;

    // Ignore code 0
    if (receivedCode == 0) {
      IrReceiver.resume(); // Ready to receive the next signal
      return;
    }

    Serial.print("Received IR Code: ");
    Serial.println(receivedCode, HEX);

    // Handle the received IR code
    switch (receivedCode) {
      case 0xBC43FF00: // On/Off
        Serial.println("[DEBUG] Toggle Motor Command Received");
        toggleMotor();
        break;
      case 0xEA15FF00: // Increase speed
        Serial.println("[DEBUG] Increase Speed Command Received");
        increaseSpeed();
        break;
      case 0xF807FF00: // Decrease speed
        Serial.println("[DEBUG] Decrease Speed Command Received");
        decreaseSpeed();
        break;
      case 0xF609FF00: // Switch direction
        Serial.println("[DEBUG] Switch Direction Command Received");
        switchDirection();
        break;
      case 0xBF40FF00: // Servo move left
        Serial.println("[DEBUG] Move Servo Left Command Received");
        moveServoLeft();
        break;
      case 0xBB44FF00: // Servo move right
        Serial.println("[DEBUG] Move Servo Right Command Received");
        moveServoRight();
        break;
    }

    IrReceiver.resume(); // Ready to receive the next signal
  }
}

// Motor Control Functions
void toggleMotor() {
  motorOn = !motorOn;
  if (motorOn) {
    motorSpeed = 128; // Start at 50% of max speed (PWM: 128)
    analogWrite(EN1, motorSpeed);
    setMotorDirection(false); // Default to forward
    Serial.println("[DEBUG] Motor ON at 50% speed (PWM: 128)");
    Serial.println("[DEBUG] Motor Direction: Forward");
  } else {
    analogWrite(EN1, 0); // Stop motor
    Serial.println("[DEBUG] Motor OFF");
  }
}

void increaseSpeed() {
  if (motorOn) {
    int oldSpeed = motorSpeed;
    motorSpeed = min(motorSpeed + 32, 255); // Increment speed by 1/8th of max (32 PWM units)
    analogWrite(EN1, motorSpeed);
    Serial.print("[DEBUG] Motor Speed Increased from ");
    Serial.print(oldSpeed);
    Serial.print(" to ");
    Serial.println(motorSpeed);
  } else {
    Serial.println("[DEBUG] Motor is OFF. Cannot increase speed.");
  }
}

void decreaseSpeed() {
  if (motorOn) {
    int oldSpeed = motorSpeed;
    motorSpeed = max(motorSpeed - 32, 128); // Decrement speed by 1/8th of max (32 PWM units), min is 128
    analogWrite(EN1, motorSpeed);
    Serial.print("[DEBUG] Motor Speed Decreased from ");
    Serial.print(oldSpeed);
    Serial.print(" to ");
    Serial.println(motorSpeed);
  } else {
    Serial.println("[DEBUG] Motor is OFF. Cannot decrease speed.");
  }
}

void switchDirection() {
  if (motorOn) {
    motorDirection = !motorDirection;
    motorSpeed = 128; // Reset speed to 50% on direction change
    analogWrite(EN1, motorSpeed);
    setMotorDirection(motorDirection);
    Serial.print("[DEBUG] Motor Direction Switched to ");
    Serial.println(motorDirection ? "Forward" : "Backward");
    Serial.println("[DEBUG] Motor Reset to 50% speed (PWM: 128)");
  } else {
    Serial.println("[DEBUG] Motor is OFF. Cannot switch direction.");
  }
}

void setMotorDirection(bool forward) {
  if (forward) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
}

// Servo Control Functions
void moveServoLeft() {
  int oldPosition = servoPosition;
  servoPosition = max(servoPosition - 10, 0); // Decrease position, minimum 0
  myServo.write(servoPosition);
  Serial.print("[DEBUG] Servo Moved Left from ");
  Serial.print(oldPosition);
  Serial.print(" to ");
  Serial.println(servoPosition);
}

void moveServoRight() {
  int oldPosition = servoPosition;
  servoPosition = min(servoPosition + 10, 180); // Increase position, maximum 180
  myServo.write(servoPosition);
  Serial.print("[DEBUG] Servo Moved Right from ");
  Serial.print(oldPosition);
  Serial.print(" to ");
  Serial.println(servoPosition);
}
