#include <SoftwareSerial.h>

int motherReader = 6;
int motherWriter = 7;

// Led variables
int ledPin1 = 2;
int ledPin2 = 3;
int ledPin3 = 4;
int ledIterator = 0;

// Button variables
int butVal = 0;
int butPin = 5;

int ledList[3];

// Cable variables
int cablePin1 = 8;
int cablePin2 = 9;
int cablePin3 = 10;
int cablePin4 = 11;
int cablePin5 = 12;
int cablePin6 = 13;

int cableVal1 = 0;
int cableVal2 = 0;
int cableVal3 = 0;
int correctList[3];

bool isGameFinished = false;
bool hasSendData = false;

int currentRandom = 0;

void setup() {
  Serial.begin(9600);

  // Leds setup
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // Button setup
  pinMode(butPin, INPUT);

  // Output setup
  pinMode(cablePin1, OUTPUT);
  pinMode(cablePin2, OUTPUT);
  pinMode(cablePin3, OUTPUT);
  pinMode(cablePin4, OUTPUT);
  pinMode(cablePin5, OUTPUT);
  pinMode(cablePin6, OUTPUT);

  // Mother link setup
  pinMode(motherReader, INPUT);
  pinMode(motherWriter, OUTPUT);

  // Define current correct cables
  randomSeed(analogRead(A0));
  setupRandomOutputs();
  digitalWrite(motherWriter, LOW);
}

void setupRandomOutputs() {
  for (int i = 0; i < 3; i++) {
    int currentLength = sizeof(correctList) / sizeof(correctList[0]);
    while (correctList[i] == 0) {
      int newValue = random(1, 7);
      if (!checkValueInArray(correctList, currentLength, newValue)) {
        correctList[i] = newValue;
        continue;
      }
    }
  }

  // Print current correct answer
  for (int i = 0; i < 3; i++) {
    Serial.print("Array[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(correctList[i]);
  }
}

bool checkValueInArray(int *array, int arrayLength, int value) {
  for (int j = 0; j < arrayLength; j++) {
    if (array[j] == value) {
      return true;
    }
  }
  return false;
}

void checkMother() {
  if (digitalRead(motherReader) == HIGH) {
    Serial.println("MOTHER SAID: RESET");
    isGameFinished = false;
    hasSendData = false;
    correctList[0] = 0;
    correctList[1] = 0;
    correctList[2] = 0;
    analogWrite(ledPin1, 0);
    analogWrite(ledPin2, 0);
    analogWrite(ledPin3, 0);
    setupRandomOutputs();
  }
}


void loop() {
  checkMother();
  if (isGameFinished == false) {
    // Check if mother has send a reset

    cableVal1 = digitalRead(correctList[0] + 7);
    cableVal2 = digitalRead(correctList[1] + 7);
    cableVal3 = digitalRead(correctList[2] + 7);
    // Serial.print("Current cable value: ");
    // Serial.print(cableVal1);
    // Serial.print(" / ");
    // Serial.print(cableVal2);
    // Serial.print(" / ");
    // Serial.println(cableVal3);

    // Check button status
    butVal = digitalRead(butPin);

    // Fill current LEDs values
    if (butVal == HIGH) {
      ledList[0] = 0;
      ledList[1] = 0;
      ledList[2] = 0;
      ledIterator = 0;
      if (cableVal1 == 1) {
        ledList[ledIterator] = 255;
        ledIterator++;
      }
      if (cableVal2 == 1) {
        ledList[ledIterator] = 255;
        ledIterator++;
      }
      if (cableVal3 == 1) {
        ledList[ledIterator] = 255;
        ledIterator++;
      }
      analogWrite(ledPin1, ledList[0]);
      analogWrite(ledPin2, ledList[1]);
      analogWrite(ledPin3, ledList[2]);
      if (ledList[0] == 255 && ledList[1] == 255 && ledList[2] == 255) {
        isGameFinished = true;
      }
    }
  } else {
    digitalWrite(motherWriter, HIGH);
    Serial.println("It's a win!");
    delay(100);
    digitalWrite(motherWriter, LOW);
  }
}