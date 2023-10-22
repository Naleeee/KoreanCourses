#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include <SoftwareSerial.h>
#include <LedControl.h>
#include <millisDelay.h>

// LCD variables
LiquidCrystal_I2C LCD(0x27, 16, 2); // définit le type d'ecran lcd 16 x 2

// Bluetooth variables
int TXPin = 6;
int RXPin = 7;
SoftwareSerial BT(TXPin, RXPin); 

// LEDs variables
int failLed = 3;
int winLed = 4;

// Matrix variables
int DIN = 12; 
int CS =  11;
int CLK = 10;
LedControl lc = LedControl(DIN, CLK, CS, 0);
int currentArrow[8][8];
int currentArrowNumber;
int arrowUp[8][8] = {
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1, 1, 1, 0},
  {0, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
};
int arrowDown[8][8] = {
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0},
  {0, 1, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
};
int arrowLeft[8][8] = {
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
};
int arrowRight[8][8] = {
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
};

// Timer variables
millisDelay timerArrows;
millisDelay timerLeds;
int speed = 5000;

String score = "0";
int streak = 0;

void setup(){
  Serial.begin(9600);
  randomSeed(analogRead(A1));

  // LCD setup
  LCD.init(); // initialisation de l'afficheur
  LCD.backlight();
  LCD.setCursor(1, 0);
  LCD.print("STREAK: x");
  LCD.setCursor(1, 1);
  LCD.print("SCORE:");

  // Bluetooth setup
  BT.begin(9600);

  // LEDs setup
  pinMode(failLed, OUTPUT);
  pinMode(winLed, OUTPUT);

  // Matrix setup
  lc.shutdown(0, false);
  lc.setIntensity(0, 15);
  lc.clearDisplay(0);
  lc.setIntensity(0, LOW);
  defineNewArrow();

  // Timer setup
  timerArrows.start(speed);
}

void loop(){
  LCD.setCursor(10, 0);
  LCD.print(streak);
  LCD.setCursor(8, 1);
  LCD.print(score);
  LCD.display();
  printMatrix();

  if (BT.available()) {
    checkInput(BT.read());
    // Serial.write(BT.read().toInt());
  }
  
  if (timerArrows.justFinished()) {
    // Serial.println("Timer Down");
    analogWrite(failLed, 255);
    defineNewArrow();
    streak = 0;
    speed += 200;
    LCD.setCursor(10, 0);
    LCD.print("      ");
    timerLeds.start(speed / 2);
    timerArrows.start(speed);
  }
  // Serial.print("Speed ");
  // Serial.println(speed);

  if (timerLeds.justFinished()) {
    analogWrite(winLed, 0);
    analogWrite(failLed, 0);
  }
}

void checkInput(int receivedInput) {
  analogWrite(winLed, 0);
  analogWrite(failLed, 0);

  Serial.println("------------------------------");

  if (receivedInput - 48 == currentArrowNumber) {
    speed -= 200;
    streak += 1;
    Serial.print("Score ");
    Serial.print(score);
    Serial.print(" + ");
    Serial.println((10000 - speed) * streak);
    score = score.toInt() + (1000 * streak);
    Serial.print("Final Score ");
    Serial.println(score);
    timerArrows.start(speed);
    timerLeds.start(speed / 2);
    analogWrite(winLed, 255);
  } else {
    streak = 0;
    speed += 200;
    LCD.setCursor(10, 0);
    LCD.print("      ");
    timerArrows.start(speed);
    timerLeds.start(speed / 2);
    analogWrite(failLed, 255);
  }
  defineNewArrow(); 
}

void defineNewArrow() {
  lc.clearDisplay(0);
  currentArrowNumber = random(1, 5);
  delay(100);
  switch (currentArrowNumber) {
    case 1:
      setCurrentArrow(arrowUp);
      break;
    case 2:
      setCurrentArrow(arrowDown);
      break;
    case 3:
      setCurrentArrow(arrowRight);
      break;
    case 4:
      setCurrentArrow(arrowLeft);
      break;
    default:
      break;
  }
}

void setCurrentArrow(int arrow[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      currentArrow[i][j] = arrow[i][j];
    }
  }
}

void printMatrix() {
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if (currentArrow[i][j] < 2) {
        lc.setLed(0, i, j, currentArrow[i][j]);
      } else {
        lc.setLed(0, i, j, 0);
      }
    }
  }
}