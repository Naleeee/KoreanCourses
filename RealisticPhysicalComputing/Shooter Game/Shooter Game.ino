#include <Servo.h>

int potVal = 0;
int potPin = A0;

int butVal = 0;
int butPin = 3;

Servo myservo;
int servoPin = 12;
int servoVal = 0;

int gameLedPin1 = 5;
int gameLedVal1 = 0;

int gameLedPin2 = 6;
int gameLedVal2 = 0;

int gameLedPin3 = 7;
int gameLedVal3 = 0;

int gameLedPin4 = 8;
int gameLedVal4 = 0;

int currentLed = 1;

void setup() {
  Serial.begin(9600);

  // Init Button
  pinMode(butPin, INPUT);

  // Init Servomotor
  myservo.attach(servoPin);

  // Init LEDs
  pinMode(gameLedPin1, OUTPUT);
  pinMode(gameLedPin2, OUTPUT);
  pinMode(gameLedPin3, OUTPUT);
  pinMode(gameLedPin4, OUTPUT);

  randomSeed(analogRead(A1));
  currentLed = random(1, 5);
}

void loop() {
  // Update servomotor value
  potVal = analogRead(potPin);
  servoVal = map(potVal, 0, 1023, 0, 180);
  myservo.write(servoVal);
  // Serial.print("Servo value: ");
  // Serial.println(servoVal);
  delay(15);

  // Check the button status
  butVal = digitalRead(butPin);
  // Serial.print("Buton value: ");
  // Serial.println(butVal);
  
  if (currentLed == 1) {
      analogWrite(gameLedPin1, 255);
  } else if (currentLed == 2) {
      analogWrite(gameLedPin2, 255);
  } else if (currentLed == 3) {
      analogWrite(gameLedPin3, 255);
  } else if (currentLed == 4) {
      analogWrite(gameLedPin4, 255);
  }

  if (butVal == HIGH) {
    if (servoVal > 120 && servoVal < 132 && currentLed == 1) {
      analogWrite(gameLedPin1, 0);
      delay(500);
      currentLed = random(1, 5);
    } else if (servoVal > 88 && servoVal < 100 && currentLed == 2) {
      analogWrite(gameLedPin2, 0);
      delay(500);
      currentLed = random(1, 5);
    } else if (servoVal > 66 && servoVal < 78 && currentLed == 3) {
      analogWrite(gameLedPin3, 0);
      delay(500);
      currentLed = random(1, 5);
    } else if (servoVal > 32 && servoVal < 44 && currentLed == 4) {
      analogWrite(gameLedPin4, 0);
      delay(500);
      currentLed = random(1, 5);
    }
  }
}