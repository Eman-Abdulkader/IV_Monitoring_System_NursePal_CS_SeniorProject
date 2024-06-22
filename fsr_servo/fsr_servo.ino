#include <Servo.h>

#define FSR_PIN A0     // Define the pin to which the FSR is connected
#define SERVO_PIN 9    // Define the pin to which the servo is connected

Servo servoMotor;     // Create a servo object

void setup() {
  Serial.begin(9600); // Initialize serial communication
  servoMotor.attach(SERVO_PIN); // Attach the servo to its pin
}

void loop() {
  // Read the analog value from the FSR
  int fsrValue = analogRead(FSR_PIN);

  // You may need to adjust this threshold value based on your FSR and circuit
  int threshold = 100; // Example threshold value

  // Check if pressure is detected
  if (fsrValue > threshold) {
    // Move the servo to 180 degrees
    servoMotor.write(180);
    String data = "{\"IV\": \"Not Done\"}"; // Create JSON string for IV not done
    Serial.println(data); // Print the JSON string
  } else {
    // Move the servo to 90 degrees
    servoMotor.write(90);
    String data = "{\"IV\": \"Done\"}"; // Create JSON string for IV done
    Serial.println(data); // Print the JSON string
  }

  delay(1000); // Delay to slow down the output for better readability
}
