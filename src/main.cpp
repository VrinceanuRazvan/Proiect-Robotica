#include <Arduino.h>
#include <Servo.h>

// Pin Definitions
const int EN1 = 9;  // Enable pin for Motor 1 (PWM)
const int IN1 = 8;  // Input 1 for Motor 1
const int IN2 = 7;  // Input 2 for Motor 1
const int SERVO_PIN = 6; // Pin for the Servo
const int ANALOG_PIN = A1; // Analog pin to read

Servo myServo; // Create a Servo object

void setup() {
  // Configure the motor pins as OUTPUT 
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Set initial state for motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN1, 0);  // Motor stopped initially

  // Attach the servo to the specified pin and move to the neutral position
  myServo.attach(SERVO_PIN);
  myServo.write(90); // Neutral position (90 degrees)

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Move Motor Forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN1, 255);  // Adjust speed (0-255)

  // Read the analog value from A1
  int analogValue = analogRead(ANALOG_PIN);
  Serial.print("Analog Value from A1: ");
  Serial.println(analogValue);
  delay(100);
  // The servo remains at the neutral position
}
