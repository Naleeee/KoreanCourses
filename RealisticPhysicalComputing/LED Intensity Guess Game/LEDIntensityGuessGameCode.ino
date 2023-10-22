int potVal = 0;
int potPin = A0;

int butVal = 0;
int butPin = 5;

int gameLedVal = 0;
int gameLedPin = 11;

int displayLedVal;
int displayLedPin = 10;

int winLedPin = 7;

int loseLedPin = 8;

void setup() {
  Serial.begin(9600);

  // Init Button
  pinMode(butPin, INPUT);

  // Init Leds
  pinMode(gameLedPin, OUTPUT);
  pinMode(displayLedPin, OUTPUT);
  pinMode(winLedPin, OUTPUT);
  pinMode(loseLedPin, OUTPUT);

  // Setup value to guess
  randomSeed(analogRead(A0));
  displayLedVal = random(0, 256);
  Serial.print("Value to guess: ");
  Serial.println(displayLedVal);
  analogWrite(displayLedPin, displayLedVal);
}

void loop() {
  // Get current guess
  potVal = analogRead(potPin);
  gameLedVal = potVal / 4;
  // Serial.print("Game Led brightness: ");
  // Serial.println(gameLedVal);
  analogWrite(gameLedPin, gameLedVal);

  // Check button status
  butVal = digitalRead(butPin);
  // Serial.print("Button value: ");
  // Serial.println(butVal);
  if (butVal == HIGH) {
    if (displayLedVal - 20 < gameLedVal && displayLedVal + 20 > gameLedVal) {
      Serial.println("LFG ! You win ! Let's play again...");
      analogWrite(winLedPin, 255);

      for (int i = 0; i < 10; i++) {
        analogWrite(displayLedPin, 255);
        analogWrite(gameLedPin, 0);
        delay(100);
        analogWrite(displayLedPin, 0);
        analogWrite(gameLedPin, 255);
        delay(100);
      }

      displayLedVal = random(0, 256);
      Serial.print("Value to guess: ");
      Serial.println(displayLedVal);
      analogWrite(displayLedPin, displayLedVal);
    } else {
      Serial.println("WRONG ANSWER");
      Serial.print("Current value: ");
      Serial.println(gameLedVal);
      analogWrite(loseLedPin, 255);
      delay(1000);
    }
    analogWrite(winLedPin, 0);
    analogWrite(loseLedPin, 0);
  } else {
      analogWrite(winLedPin, 0);
      analogWrite(loseLedPin, 0);
  }
}
