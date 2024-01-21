// Constants
const int xPin = A2; // Joystick X-axis
const int yPin = A1; // Joystick Y-axis

void setup() {
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the position of the joystick on the X-axis
  int xPos = analogRead(xPin);
  
  // Read the position of the joystick on the Y-axis
  int yPos = analogRead(yPin);
  
  // Send the X and Y position over the serial connection
  Serial.print("X: ");
  Serial.print(xPos);
  Serial.print(" Y: ");
  Serial.println(yPos);
  
  // Wait for a bit before taking the next reading
  delay(100);
}